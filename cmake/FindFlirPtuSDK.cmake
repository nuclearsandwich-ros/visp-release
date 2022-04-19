# See http://visp.inria.fr for more information.
#
# This software was developed at:
# Inria Rennes - Bretagne Atlantique
# Campus Universitaire de Beaulieu
# 35042 Rennes Cedex
# France
#
# If you have questions regarding the use of this file, please contact
# Inria at visp@inria.fr
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# Description:
# Try to find Kinova Jaco Robot SDK
#
# FLIRPTUSDK_FOUND
# FLIRPTUSDK_INCLUDE_DIRS
# FLIRPTUSDK_LIBRARIES
#
# Authors:
# Fabien Spindler
#
#############################################################################

set(FLIRPTUSDK_INC_SEARCH_PATH)
list(APPEND FLIRPTUSDK_INC_SEARCH_PATH /usr/include)
list(APPEND FLIRPTUSDK_INC_SEARCH_PATH /usr/include/cerial)
list(APPEND FLIRPTUSDK_INC_SEARCH_PATH "$ENV{FLIRPTUSDK_HOME}")
list(APPEND FLIRPTUSDK_INC_SEARCH_PATH "$ENV{FLIRPTUSDK_HOME}/cerial")
list(APPEND FLIRPTUSDK_INC_SEARCH_PATH "${FLIRPTUSDK_HOME}")
list(APPEND FLIRPTUSDK_INC_SEARCH_PATH "${FLIRPTUSDK_HOME}/cerial")


set(FLIRPTUSDK_LIB_SEARCH_PATH)
list(APPEND FLIRPTUSDK_LIB_SEARCH_PATH /usr/lib)
list(APPEND FLIRPTUSDK_LIB_SEARCH_PATH "$ENV{FLIRPTUSDK_HOME}")
list(APPEND FLIRPTUSDK_LIB_SEARCH_PATH "${FLIRPTUSDK_HOME}")

if(MSVC)
  if(CMAKE_CL_64)
    list(APPEND FLIRPTUSDK_LIB_SEARCH_PATH "$ENV{FLIRPTUSDK_HOME}/build/visual_studio_2008/x64/Release")
  else()
    list(APPEND FLIRPTUSDK_LIB_SEARCH_PATH "$ENV{FLIRPTUSDK_HOME}/build/visual_studio_2008/Release")
  endif()
endif()

find_path(FLIRPTUSDK_CPI_INCLUDE_DIR cpi.h
  PATHS
    ${FLIRPTUSDK_INC_SEARCH_PATH}
)

find_path(FLIRPTUSDK_CERIAL_INCLUDE_DIR cerial.h
  PATHS
    ${FLIRPTUSDK_INC_SEARCH_PATH}
)

find_library(FLIRPTUSDK_LIBRARIES
  NAMES CPI2.lib libcpi.a
  PATHS
    ${FLIRPTUSDK_LIB_SEARCH_PATH}
)

if(FLIRPTUSDK_LIBRARIES AND FLIRPTUSDK_CPI_INCLUDE_DIR AND FLIRPTUSDK_CERIAL_INCLUDE_DIR)
  set(FLIRPTUSDK_INCLUDE_DIRS ${FLIRPTUSDK_CPI_INCLUDE_DIR} ${FLIRPTUSDK_CERIAL_INCLUDE_DIR})
  set(FLIRPTUSDK_FOUND TRUE)
else()
  set(FLIRPTUSDK_FOUND FALSE)
endif()

mark_as_advanced(
  FLIRPTUSDK_INCLUDE_DIRS
  FLIRPTUSDK_CPI_INCLUDE_DIR
  FLIRPTUSDK_CERIAL_INCLUDE_DIR
  FLIRPTUSDK_LIBRARIES
  FLIRPTUSDK_INC_SEARCH_PATH
  FLIRPTUSDK_LIB_SEARCH_PATH
)

