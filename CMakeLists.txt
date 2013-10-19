cmake_minimum_required(VERSION 2.8)
project(LFLL CXX)

  
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
set(INSTALL_CMAKE_DIR "${CMAKE_ROOT}/Modules" CACHE PATH
  "Installation directory for CMake files")


add_subdirectory(lfll)
add_subdirectory(tests)
add_subdirectory(example)


# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE LFLL)


# Install FindLFLL.cmake
install(FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/FindLFLL.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}")

