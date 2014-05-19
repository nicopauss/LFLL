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

if (${STRICT_MODE})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4290 /wd4702")
    endif()
else()
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX-")
    endif()
endif()

set(FUZZYLITE_URL
    https://code.google.com/p/fuzzylite/
)
set(FUZZYLITE_GIT_BRANCH
    fuzzylite-4.x
)
set(FUZZYLITE_PREFIX
    ${CMAKE_CURRENT_BINARY_DIR}/fuzzylite
)
set(FUZZYLITE_SRC_DIR
    ${FUZZYLITE_PREFIX}/src/fuzzylite/fuzzylite
)

set(FUZZYLITE_CMAKE_ARGS
	-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
	-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
	-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
)

if(MSVC)
	set(FUZZYLITE_LIB_DIR 
		${FUZZYLITE_PREFIX}/bin
	)
	set(FUZZYLITE_INCLUDE_DIR 
		${FUZZYLITE_PREFIX}/include
	)
	set(FUZZYLITE_EXT_LIB
		DbgHelp.lib
	)
	set(FUZZYLITE_CMAKE_ARGS
		${FUZZYLITE_CMAKE_ARGS}
		-DCMAKE_INSTALL_PREFIX:PATH=${FUZZYLITE_PREFIX}
	)
else()
	set(FUZZYLITE_LIB_DIR 
		${FUZZYLITE_PREFIX}/src/fuzzylite-build/bin
	)
	set(FUZZYLITE_INCLUDE_DIR 
		${FUZZYLITE_SRC_DIR}
	)
	set(FUZZYLITE_EXT_LIB
	)
endif()

set(FUZZYLITE_LIB_NAME 
	${CMAKE_STATIC_LIBRARY_PREFIX}fuzzylite-static${CMAKE_STATIC_LIBRARY_SUFFIX}
)

set(FUZZYLITE_LIB
    ${FUZZYLITE_LIB_DIR}/${FUZZYLITE_LIB_NAME}
)

include(ExternalProject)

if(MSVC)
	ExternalProject_Add(
		fuzzylite
		GIT_REPOSITORY ${FUZZYLITE_URL}
		GIT_TAG ${FUZZYLITE_GIT_BRANCH}
		PREFIX ${FUZZYLITE_PREFIX}
		INSTALL_DIR ${FUZZYLITE_PREFIX}
		CONFIGURE_COMMAND ${CMAKE_COMMAND} ${FUZZYLITE_CMAKE_ARGS} ${FUZZYLITE_SRC_DIR}
	)
else()
	ExternalProject_Add(
		fuzzylite
		GIT_REPOSITORY ${FUZZYLITE_URL}
		GIT_TAG ${FUZZYLITE_GIT_BRANCH}
		PREFIX ${FUZZYLITE_PREFIX}
		CONFIGURE_COMMAND ${CMAKE_COMMAND} ${FUZZYLITE_CMAKE_ARGS} ${FUZZYLITE_SRC_DIR}
		BUILD_COMMAND $(MAKE) "fl-static"
		INSTALL_COMMAND ""
	)
endif()

include_directories(${FUZZYLITE_INCLUDE_DIR})

add_library(fuzzylite_static STATIC IMPORTED)
set_property(TARGET fuzzylite_static PROPERTY IMPORTED_LOCATION ${FUZZYLITE_LIB})
add_dependencies(fuzzylite_static fuzzylite)

add_executable(benchmarks_fuzzylite ${SOURCES_FILES})
add_dependencies(benchmarks_fuzzylite hayai fuzzylite_static)
target_link_libraries(benchmarks_fuzzylite fuzzylite_static ${FUZZYLITE_EXT_LIB})
if (${NEED_RT_LIB})
    target_link_libraries(benchmarks_fuzzylite rt)
endif()

