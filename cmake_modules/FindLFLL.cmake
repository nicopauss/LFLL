# - FindLFLL.cmake
# This module can be used to find LFLL.
#
# The following variables will be defined for your use:
#
#  LFLL_FOUND           = LFLL found
#  LFLL_INCLUDE_DIR    = The LFLL include directory
#  LFLL_VERSION_STRING  = A human-readable version of the LFLL (e.g. 1.0.1)
#
# Typical usage could be something like this:
#   find_package(LFLL REQUIRED)
#   include_directories(${LFLL_INCLUDE_DIRS})
#

#=============================================================================
# Copyright (c) 2013 Nicolas Pauss <nicolas.pauss@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file COPYING-CMAKE-MODULES for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================


find_path(LFLL_INCLUDE_DIR
          NAMES lfll/LFLL.h
          PATHS 
          /usr/include
          /usr/local/include
          /opt/local/include
          ..
          DOC "The LFLL include directory")


if(NOT LFLL_INCLUDE_DIR)
    set(ERROR_MESSAGE "LFLL not found")
    if(LFLL_FIND_REQUIRED)
        message(FATAL_ERROR ${ERROR_MESSAGE})
    else(LFLL_FIND_REQUIRED)
        message(WARNING ${ERROR_MESSAGE})
    endif(LFLL_FIND_REQUIRED)
    set(LFLL_FOUND false)
    set(LFLL_VERSION_STRING "")
    
    
else(NOT LFLL_INCLUDE_DIR)
    
    
    file(STRINGS "${LFLL_INCLUDE_DIR}/lfll/LFLL.h"
         LFLL_MAJOR_VERSION_STRING REGEX "^#define LFLL_MAJOR_VERSION [0-9]+$")
    file(STRINGS "${LFLL_INCLUDE_DIR}/lfll/LFLL.h"
         LFLL_MINOR_VERSION_STRING REGEX "^#define LFLL_MINOR_VERSION [0-9]+$")
    file(STRINGS "${LFLL_INCLUDE_DIR}/lfll/LFLL.h"
         LFLL_PATCH_VERSION_STRING REGEX "^#define LFLL_PATCH_VERSION [0-9]+$")
         
    if(LFLL_MAJOR_VERSION_STRING AND LFLL_MINOR_VERSION_STRING AND LFLL_PATCH_VERSION_STRING)
    
        string(REGEX
               REPLACE "^#define LFLL_MAJOR_VERSION ([0-9]+)$" "\\1"
               LFLL_MAJOR_VERSION_STRING ${LFLL_MAJOR_VERSION_STRING})
        string(REGEX
               REPLACE "^#define LFLL_MINOR_VERSION ([0-9]+)$" "\\1"
               LFLL_MINOR_VERSION_STRING ${LFLL_MINOR_VERSION_STRING})
        string(REGEX
               REPLACE "^#define LFLL_PATCH_VERSION ([0-9]+)$" "\\1"
               LFLL_PATCH_VERSION_STRING ${LFLL_PATCH_VERSION_STRING})
        
        set(LFLL_VERSION_STRING "${LFLL_MAJOR_VERSION_STRING}.${LFLL_MINOR_VERSION_STRING}.${LFLL_PATCH_VERSION_STRING}")
        set(LFLL_FOUND true)
    else()
        set(ERROR_MESSAGE "LFLL version string not found")
        if(LFLL_FIND_REQUIRED)
            message(FATAL_ERROR ${ERROR_MESSAGE})
        else(LFLL_FIND_REQUIRED)
            message(WARNING ${ERROR_MESSAGE})
        endif(LFLL_FIND_REQUIRED)
        set(LFLL_VERSION_STRING "")
        set(LFLL_FOUND false)
    endif()

endif(NOT LFLL_INCLUDE_DIR)

mark_as_advanced(LFLL_INCLUDE_DIR LFLL_FOUND LFLL_VERSION_STRING)