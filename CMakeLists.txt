cmake_minimum_required(VERSION 2.8)
project(LFLL CXX)

  
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
set(INSTALL_CMAKE_DIR "${CMAKE_ROOT}/Modules" CACHE PATH
  "Installation directory for CMake files")

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

  
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lfll")

# lfll custom target
file(GLOB_RECURSE HEADERS_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SOURCE_DIR}/*.h")
install(DIRECTORY ${SOURCE_DIR}
    DESTINATION "${INSTALL_INCLUDE_DIR}"
	FILES_MATCHING PATTERN "*.h")
add_custom_target(lfll SOURCES ${HEADERS_FILES})


add_subdirectory(tests)
add_subdirectory(examples)

export(PACKAGE LFLL)

# Install FindLFLL.cmake
install(FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/FindLFLL.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}")

