# -*- cmake -*- 
#######################################################################
# Software License Agreement (BSD License)                            #
#                                                                     #
#  Copyright (c) 2011, MBARI.                                         #
#  All rights reserved.                                               #
#                                                                     #
#  Redistribution and use in source and binary forms, with or without #
#  modification, are permitted provided that the following conditions #
#  are met:                                                           #
#                                                                     #
#   * Redistributions of source code must retain the above copyright  #
#     notice, this list of conditions and the following disclaimer.   #
#   * Redistributions in binary form must reproduce the above         #
#     copyright notice, this list of conditions and the following     #
#     disclaimer in the documentation and/or other materials provided #
#     with the distribution.                                          #
#   * Neither the name of the TREX Project nor the names of its       #
#     contributors may be used to endorse or promote products derived #
#     from this software without specific prior written permission.   #
#                                                                     #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS #
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT   #
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS   #
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE      #
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, #
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,#
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;    #
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER    #
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT  #
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN   #
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE     #
# POSSIBILITY OF SUCH DAMAGE.                                         #
#######################################################################

install(DIRECTORY scripts/ DESTINATION bin OPTIONAL
  FILES_MATCHING PATTERN "*"
  PATTERN "*.in" EXCLUDE
  PATTERN ".svn" EXCLUDE)
set_property(GLOBAL APPEND PROPERTY ${PROJECT_NAME}_CMDS
  ${CMAKE_CURRENT_SOURCE_DIR}/scripts)


bash_path(TREX_CONFIG_DIRS ${PROJECT_NAME}_CFGS)
bash_path(TREX_LIBRARY_DIRS ${PROJECT_NAME}_LIBS)
bash_path(TREX_BINARY_DIRS ${PROJECT_NAME}_CMDS)
bash_path(TREX_PYTHON ${PROJECT_NAME}_PYTHON)

# A file just for testing inside the build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/trex_devel.bash.in
  ${CMAKE_CURRENT_BINARY_DIR}/trex_devel.bash @ONLY)

# create a default bash environement file for installed version
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/trex_init.bash.in
  ${CMAKE_CURRENT_BINARY_DIR}/trex_init.bash @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/trex_init.bash DESTINATION ${TREX_SHARED})

configure_file(cmake/trex-config-version.cmake.in 
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/trex-config-version.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/trex-config-version.cmake 
  DESTINATION share/trex/cmake)



file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/log)
file(WRITE ${CMAKE_BINARY_DIR}/log/.empty_file " ") # Not really empty ... it is just to force tar to use it

# create the default log directory ... everybody can read/write/exec
install(DIRECTORY ${CMAKE_BINARY_DIR}/log DESTINATION ${TREX_SHARED}
   DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE 
    GROUP_READ GROUP_WRITE GROUP_EXECUTE
    WORLD_READ WORLD_WRITE WORLD_EXECUTE
   FILES_MATCHING PATTERN "latest" EXCLUDE
   PATTERN "????.???.*" EXCLUDE
   PATTERN "archives" EXCLUDE
   PATTERN ".empty_file")

get_property(TREX_INCS GLOBAL PROPERTY TREX_INCLUDES)
get_property(trex-core GLOBAL PROPERTY trex-core)
get_property(trex-extra GLOBAL PROPERTY trex-extra)
get_property(trex-python GLOBAL PROPERTY trex-python)
list(REMOVE_DUPLICATES TREX_INCS)
if(CPP11_ENABLED)
  set(trex_FLAGS ${CPP11_COMPILER_SWITCH})
endif(CPP11_ENABLED)
configure_file(cmake/trex-config.cmake.in 
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/trex-config.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/trex-config.cmake 
  DESTINATION share/trex/cmake)
unset(TREX_INCS)

# All the packages are mixed together so older version of cmake are not confused
install(EXPORT trex-targets DESTINATION share/trex/cmake/imports OPTIONAL)

#include(CMakePackageConfigHelpers)
# Note I need to do a real version checking
#write_basic_package_version_file(trexConfigVersion.cmake VERSION ${VERSION} COMPATIBILITY AnyNewerVersion)
