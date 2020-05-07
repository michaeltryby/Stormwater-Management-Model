#!/usr/bin/env zsh

# relocate.zsh - Relocate libomp to install/extern
#
# Arguments:
#   1 - Path to library
#


echo "INFO: Relocating ... $1"

#[[ ! -d extern ]] && { mkdir -v extern }


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


# install
#     extern
#         libomp.dylib
#             id
#                 /usr/local/opt/libomp/lib/libomp.dylib
#               * @rpath/libomp.dylib
#             load
#                 none
#             rpath
#                 none
#
#     lib
#         libswmm5.dylib
#             id
#                 @rpath/libswmm5.dylib
#             load
#                 /usr/local/opt/libomp/lib/libomp.dylib
#               * @rpath/libomp.dylib
#             rpath
#                 @loader_path;@loader_path/../.dylib
#               * @loader_path/../extern
#
#     src/swmm/toolkit
#         _solver.so
#             id
#                 none
#             load
#                 @rpath/libswmm5.dylib
#                 /usr/local/opt/libomp/lib/libomp.dylib
#               * @rpath/libomp.dylib
#             rpath
#                 @loader_path/../../../..
#               * @loader_path/../../../..;@loader_path/../../../../extern
