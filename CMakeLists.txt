cmake_minimum_required(VERSION 2.8)
project(LFLL CXX C)

  
set(INSTALL_INCLUDE_DIR include CACHE PATH
	"Installation directory for header files")
set(INSTALL_CMAKE_DIR "${CMAKE_ROOT}/Modules" CACHE PATH
	"Installation directory for CMake files")
option(STRICT_MODE "Strict mode, enable every warnings and treat warnings as errors" OFF)
option(DONT_BUILD_TESTS "Don't build unit tests" OFF)
option(DONT_BUILD_EXAMPLES "Don't build examples" OFF)
option(DONT_BUILD_BENCHMARKS "Don't build benchmarks" OFF)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'Release' as none was specified.")
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
		"MinSizeRel" "RelWithDebInfo")
endif()

# Set strict mode
if (${STRICT_MODE})
	message(STATUS "Strict mode activated")
	message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wshadow -Wno-missing-braces -Werror")
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wshadow -Wno-missing-braces -Werror")
		if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.8.0" OR
			CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.8.0")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs")
		endif()
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -w2 -Wcheck")
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX /wd4305")
	endif()
endif()

include(LFLLTarget.cmake)

if (NOT ${DONT_BUILD_TESTS})
    add_subdirectory(tests)
endif()
if (NOT ${DONT_BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()
if (NOT ${DONT_BUILD_BENCHMARKS})
    add_subdirectory(benchmarks)
endif()

export(PACKAGE LFLL)

# Install FindLFLL.cmake
install(FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/FindLFLL.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}")

