set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules")
find_package(LFLL REQUIRED)
include_directories(${LFLL_INCLUDE_DIR})
message(STATUS "LFLL_INCLUDE_DIR = ${LFLL_INCLUDE_DIR}")

add_subdirectory(mamdani)
add_subdirectory(sugeno)
add_subdirectory(openmp)

