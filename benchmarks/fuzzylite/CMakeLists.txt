set(SOURCES_FILES

main.cpp
FuzzyliteMamdaniBenchmark.cpp
FuzzyliteSugenoBenchmark.cpp
LFLLMamdaniBenchmark.cpp
LFLLSimpleMamdani.cpp
LFLLSimpleMamdani.h
LFLLSimpleSugeno.cpp
LFLLSimpleSugeno.h
LFLLSugenoBenchmark.cpp
)

set(FUZZYLITE_PREFIX
    ${CMAKE_CURRENT_BINARY_DIR}/fuzzylite
)
set(FUZZYLITE_SRC_DIR
    ${FUZZYLITE_PREFIX}/src/fuzzylite/fuzzylite
)
set(FUZZYLITE_LIB_DIR 
    ${FUZZYLITE_PREFIX}/src/fuzzylite-build/bin
)
set(FUZZYLITE_LIB 
    ${FUZZYLITE_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}fuzzylite-static${CMAKE_STATIC_LIBRARY_SUFFIX}
)

include(ExternalProject)

ExternalProject_Add(
    fuzzylite
    GIT_REPOSITORY https://code.google.com/p/fuzzylite/
    GIT_TAG fuzzylite-4.x
    PREFIX ${FUZZYLITE_PREFIX}
    CONFIGURE_COMMAND ${CMAKE_COMMAND} ${FUZZYLITE_SRC_DIR}
    BUILD_COMMAND $(MAKE) fl-static
    INSTALL_COMMAND ""
)


include_directories(${FUZZYLITE_SRC_DIR})

add_executable(benchmarks_fuzzylite ${SOURCES_FILES})
add_dependencies(benchmarks_fuzzylite hayai fuzzylite)
target_link_libraries(benchmarks_fuzzylite ${FUZZYLITE_LIB})

