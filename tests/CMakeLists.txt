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


set(CATCH_PREFIX
    ${CMAKE_CURRENT_BINARY_DIR}/catch
)
set(CATCH_SRC_DIR
    ${CATCH_PREFIX}/src/catch/single_include
)

include(ExternalProject)

ExternalProject_Add(
    catch
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
    PREFIX ${CATCH_PREFIX}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

include_directories(${CATCH_SRC_DIR})

if (${STRICT_MODE})
    # Catch warning ignore
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-extra")
        if (CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.6.0" OR
            CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.6.0")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-but-set-variable")
        endif()
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4715")
    endif()
endif()

add_executable(tests ${SOURCES_FILES})
add_dependencies(tests catch)
