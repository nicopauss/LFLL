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

if (${STRICT_MODE})
    # Catch warning ignore
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-extra")
        if (CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.6.0" OR
            CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.6.0")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-maybe-uninitialized")
        endif()
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4305 /wd4244")
    endif()
endif()


add_subdirectory(allterms)
add_subdirectory(fuzzylite)
