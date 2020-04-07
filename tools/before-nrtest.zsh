#!/usr/bin/env zsh

#
#
#


export TEST_HOME="nrtests"


# check that env variables are set
REQUIRED_VARS=('PROJECT' 'BUILD_HOME' 'PLATFORM')
for i in ${REQUIRED_VARS}; do
    [[ -v "${${(P)i}}" ]] && { echo "ERROR: $i must be defined"; return 1 }
done

# determine project directory
CUR_DIR=${PWD}
SCRIPT_HOME=${0:a:h}
cd ${SCRIPT_HOME}/..


# set URL to github repo with nrtest files
NRTESTS_URL="https://github.com/SWMM-Project/${PROJECT}-nrtestsuite"
LATEST_URL="${NRTESTS_URL}/releases/latest"


# use release tag arg else determine latest
if [[ ! -z "$1" ]]
then
    RELEASE_TAG=$1
else
    RELEASE_TAG=$( curl -sI "${LATEST_URL}" | grep -Eo 'tag\/v\S+' )
    RELEASE_TAG=$( basename ${RELEASE_TAG} )
fi

# build URLs for test and benchmark files
if [[ -v RELEASE_TAG ]]
then
  TESTFILES_URL="${NRTESTS_URL}/archive/${RELEASE_TAG}.tar.gz"
  BENCHFILES_URL="${NRTESTS_URL}/releases/download/${RELEASE_TAG}/benchmark-${PLATFORM}.tar.gz"
else
    echo "ERROR: tag %RELEASE_TAG% is invalid" ; return 1
fi


echo "INFO: Staging files for regression testing"


# create a clean directory for staging regression tests
if [[ -d ${TEST_HOME} ]]
then
  rm -rf ${TEST_HOME}
fi
mkdir ${TEST_HOME}
cd ${TEST_HOME}


# retrieve tests and benchmarks for regression testing
curl -fsSL -o nrtestfiles.tar.gz ${TESTFILES_URL}
curl -fsSL -o benchmarks.tar.gz ${BENCHFILES_URL}


# extract tests and setup symlink
tar xzf nrtestfiles.tar.gz
ln -s ./${PROJECT}-nrtestsuite-${RELEASE_TAG:1}/public tests

# create benchmark dir and extract benchmarks
mkdir benchmark
tar xzf benchmarks.tar.gz -C benchmark


# determine REF_BUILD_ID from manifest file
export REF_BUILD_ID="local"

# return user to current dir
cd ${CUR_DIR}
