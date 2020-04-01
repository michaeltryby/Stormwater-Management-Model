#!/usr/bin/env zsh

#
#  run-nrtests.zsh - Runs numerical regression test
#
#  Date Created: 4/1/2020
#
#  Author:       Michael E. Tryby
#                US EPA - ORD/CESER
#
#  Dependencies:
#    python -m pip install -r requirements.txt
#
#  Environment Variables:
#    PROJECT
#    BUILD_HOME - relative path
#    TEST_HOME  - relative path
#    PLATFORM
#    REF_BUILD_ID
#
#  Arguments:
#    1 - (SUT_VERSION)  - optional argument
#    2 - (SUT_BUILD_ID) - optional argument
#


# check that env variables are set
[[ ! -v PROJECT ]] && { echo "ERROR: PROJECT must be defined"; exit 1 }
[[ ! -v BUILD_HOME ]] && { echo "ERROR: BUILD_HOME must be defined"; exit 1 }
[[ ! -v TEST_HOME ]] && { echo "ERROR: TEST_HOME must be defined"; exit 1 }
[[ ! -v PLATFORM ]] && { echo "ERROR: PLATFORM must be defined"; exit 1 }
[[ ! -v REF_BUILD_ID ]] && { echo "ERROR: REF_BUILD_ID must be defined"; exit 1 }


# process optional arguments
if [ ! -z "$1" ]; then
    SUT_VERSION=$1
else
    SUT_VERSION="unknown"
fi

if [ ! -z "$2" ]; then
    SUT_BUILD_ID=$2
else
    SUT_BUILD_ID="local"
fi


# determine project directory
CUR_DIR=${PWD}
SCRIPT_HOME=${0:a:h}
cd ${SCRIPT_HOME}/..

# change current directory to test suite
cd ${TEST_HOME}

# check if file config file exists
if [ ! -a "./apps/${PROJECT}-${SUT_BUILD_ID}.json" ]; then
    mkdir "apps"
    ${SCRIPT_HOME}/app-config.zsh > "./apps/${PROJECT}-${SUT_BUILD_ID}.json"
fi

# recursively build test list
TESTS=$( find . -mindepth 1 -type d -follow )

# build nrtest execute command
NRTEST_EXECUTE_CMD=python3 nrtest execute
TEST_APP_PATH=apps/${PROJECT}-${SUT_BUILD_ID}.json
TEST_OUTPUT_PATH=benchmark/${PROJECT}-${SUT_BUILD_ID}

# build nrtest compare command
NRTEST_COMPARE_CMD=python3 nrtest compare
REF_OUTPUT_PATH=benchmark/${PROJECT}-${REF_BUILD_ID}
RTOL_VALUE=0.01
ATOL_VALUE=1.E-6


# if present clean test benchmark results
if [ -d "${TEST_OUTPUT_PATH}" ]; then
    rm -rf "${TEST_OUTPUT_PATH}"
fi

# perform nrtest execute
echo "INFO: Creating SUT ${SUT_BUILD_ID} artifacts"
NRTEST_COMMAND="${NRTEST_EXECUTE_CMD} ${TEST_APP_PATH} ${TESTS} -o ${TEST_OUTPUT_PATH}"
${NRTEST_COMMAND}

# perform nrtest compare
echo "INFO: Comparing SUT artifacts to REF ${REF_BUILD_ID}"
NRTEST_COMMAND="${NRTEST_COMPARE_CMD} ${TEST_OUTPUT_PATH} ${REF_OUTPUT_PATH} --rtol ${RTOL_VALUE} --atol ${ATOL_VALUE}"
${NRTEST_COMMAND}


# return user to current dir
cd ${CUR_DIR}
