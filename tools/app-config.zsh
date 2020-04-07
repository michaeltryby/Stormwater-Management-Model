#!/usr/bin/env zsh

#
#  app-config.sh - Generates nrtest app configuration file for test executable
#
#  Date Created: 11/15/2017
#       Updated: 4/1/2020
#
#  Author:       Michael E. Tryby
#                US EPA - ORD/NRMRL
#
#  Requires:
#    git
#
#  Environment Variables:
#    PROJECT
#    PLATFORM
#
#  Arguments:
#    1 - absolute path to test executable
#    2 - (SUT build id)
#


# check requirements
where git &> /dev/null
[[ ! $? ]] && { echo "ERROR: git not installed"; return 1 }

# check that env variables are set
[[ ! -v PROJECT ]] && { echo "ERROR: PROJECT must be defined"; return 1 }
[[ ! -v PLATFORM ]] && { echo "ERROR: PLATFORM must be defined"; return 1 }


# swmm target created by the cmake build script
TEST_CMD="run${PROJECT}"
# path to executable in cmake build tree
ABS_BUILD_PATH=$1

# process optional arguments
if [ ! -z "$2" ]; then
    BUILD_ID=$2
else
    BUILD_ID="unknown"
fi


# determine version
VERSION=$( git rev-parse --short HEAD )
[[ ! -v VERSION ]] && { echo "ERROR: VERSION must be determined"; return 1 }

cat<<EOF
{
    "name" : "swmm",
    "version" : "${VERSION}",
    "description" : "${PLATFORM} ${BUILD_ID}",
    "setup_script" : "",
    "exe" : "${ABS_BUILD_PATH}/${TEST_CMD}"
}
EOF
