set(SOURCES_FILES

main.cpp
LFLLTests.h
LFLLCompleteTest.cpp
engine/LFLLAggreggatorTest.cpp
engine/LFLLInputFuzzifierTest.cpp
engine/LFLLMathTest.cpp
engine/LFLLRulesEngineTest.cpp
mamdani/LFLLMamdaniDefuzzifierTest.cpp
norms/LFLLCNormTest.cpp
norms/LFLLSNormTest.cpp
norms/LFLLTNormTest.cpp
sugeno/LFLLSugenoDefuzzifierTest.cpp
terms/LFLLAccumulatedTest.cpp
terms/LFLLBellTest.cpp
terms/LFLLBooleanTest.cpp
terms/LFLLFunctionTest.cpp
terms/LFLLFunctorTest.cpp
terms/LFLLGaussianProductTest.cpp
terms/LFLLGaussianTest.cpp
terms/LFLLLRampTest.cpp
terms/LFLLPiShapeTest.cpp
terms/LFLLRectangleTest.cpp
terms/LFLLRRampTest.cpp
terms/LFLLSigmoidDifferenceTest.cpp
terms/LFLLSigmoidProductTest.cpp
terms/LFLLSigmoidTest.cpp
terms/LFLLSingletonTest.cpp
terms/LFLLSShapeTest.cpp
terms/LFLLTrapezoidTest.cpp
terms/LFLLTriangleTest.cpp
terms/LFLLZShapeTest.cpp
)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})
find_package(LFLL REQUIRED)
include_directories(${LFLL_INCLUDE_DIR})


find_path(CATCH_INCLUDE_DIR catch.hpp 
  "${CMAKE_CURRENT_SOURCE_DIR}/catch/include"
   ${CMAKE_SYSTEM_INCLUDE_DIRECTORIES}
)

message(STATUS "CATCH_INCLUDE_DIR = ${CATCH_INCLUDE_DIR}")
if(${CATCH_INCLUDE_DIR} STREQUAL "CATCH_INCLUDE_DIR-NOTFOUND")
	message(WARNING "Catch not found, unit tests have been deactivated. "
		"You should run 'git submodule init && git submodule update' before running cmake")
else()

    if (${STRICT_MODE})
        # Catch warning ignore
        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow")
        elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow")
            if (CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.6.0" OR
                CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.6.0")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-but-set-variable")
            endif()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-extra")
        elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        endif()
    endif()
    
    
    
	
	include_directories(${CATCH_INCLUDE_DIR})
	add_executable(tests ${SOURCES_FILES})	
endif()
