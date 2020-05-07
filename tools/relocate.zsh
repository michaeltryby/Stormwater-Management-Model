#!/usr/bin/env zsh

#
#  relocate.zsh - Relocate libomp to install/extern for MacOS
#
#  Date created: May 7, 2020
#
#  Author:       Michael E. Tryby
#                US EPA - ORD/CESER
#
#  Arguments:
#    1 - Path to library
#


echo "INFO: Relocating ... $1"


chmod 755 extern/$1:t


# Grabs install path for system libomp
IFS=$' '
TOKEN=($( otool -l extern/$1:t | grep LC_ID_DYLIB -A2 | grep name ))
LIB_PATH=${TOKEN[2]}


# Changes load path for libomp in _solver.so
install_name_tool -change ${LIB_PATH} @rpath/$1:t src/swmm/toolkit/_solver*.so

# Changes load path for libomp in libswmm5
install_name_tool -change ${LIB_PATH} @rpath/$1:t lib/libswmm5.dylib

# Changes id on relocated libomp
install_name_tool -id @rpath/$1:t extern/$1:t
