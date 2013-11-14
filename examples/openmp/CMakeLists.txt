set(SOURCES_FILES

OpenMpAllTerms.cpp
OpenMpAllTerms.h
main.cpp
)


find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

	add_executable(example_openmp ${SOURCES_FILES})
else()
	message(STATUS "OpenMP not found, openmp example has been deactivated")
endif()

