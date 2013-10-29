set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules")
find_package(LFLL REQUIRED)
include_directories(${LFLL_INCLUDE_DIR})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
if (MSVC) # VS2012 doesn't support correctly the tuples yet
    add_definitions(/D _VARIADIC_MAX=10)
endif()

file(GLOB_RECURSE SOURCES_FILES *.h *cpp)
add_executable(tests ${SOURCES_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc")
