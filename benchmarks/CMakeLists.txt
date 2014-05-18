set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})
find_package(LFLL REQUIRED)
include_directories(${LFLL_INCLUDE_DIR})
message(STATUS "LFLL_INCLUDE_DIR = ${LFLL_INCLUDE_DIR}")


set(HAYAI_PREFIX
    ${CMAKE_CURRENT_BINARY_DIR}/hayai
)
set(HAYAI_SRC_DIR
    ${HAYAI_PREFIX}/src/hayai/src
)

include(ExternalProject)

ExternalProject_Add(
    hayai
    GIT_REPOSITORY https://github.com/nickbruun/hayai.git
    PREFIX ${HAYAI_PREFIX}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)


include_directories(${HAYAI_SRC_DIR})

add_subdirectory(allterms)
add_subdirectory(fuzzylite)
