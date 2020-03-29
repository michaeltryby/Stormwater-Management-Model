#!/usr/bin/env zsh

#
#
#


export TEST_HOME="nrtests"


# determine project directory
CUR_DIR=${PWD}
SCRIPT_HOME=${0:a:h}
cd ${SCRIPT_HOME}/..


# set URL to github repo with nrtest files
NRTESTS_URL="https://github.com/SWMM-Project/%PROJECT%-nrtestsuite"




# return user to current dir
cd ${CUR_DIR}
