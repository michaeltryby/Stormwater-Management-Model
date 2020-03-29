#!/usr/bin/env zsh



BUILD_HOME="build"
GENERATOR="Ninja"


# determine project directory
CUR_DIR=${PWD}
SCRIPT_HOME=${0:a}
cd ${SCRIPT_HOME}/..


# perform the build
cmake -E make_directory ${BUILD_HOME}
cmake -E chdir ${BUILD_HOME} cmake -G ${GENERATOR} ..
cmake --build ./${BUILD_HOME} --target all


# return user to current dir
cd ${CUR_DIR}
