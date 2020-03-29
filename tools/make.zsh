#!/usr/bin/env zsh

#
#
#


export PROJECT="swmm"
export BUILD_HOME="build"

GENERATOR="Ninja"


# determine project directory
CUR_DIR=${PWD}
SCRIPT_HOME=${0:a:h}
cd ${SCRIPT_HOME}/..


# perform the build
cmake -E make_directory ${BUILD_HOME}
cmake -E chdir ${BUILD_HOME} cmake -G ${GENERATOR} ..
cmake --build ./${BUILD_HOME} --config Release --target all -- -v


export PLATFORM="Darwin"


# return user to current dir
cd ${CUR_DIR}
