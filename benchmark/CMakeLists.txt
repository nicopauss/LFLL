set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})
find_package(LFLL REQUIRED)
include_directories(${LFLL_INCLUDE_DIR})
message(STATUS "LFLL_INCLUDE_DIR = ${LFLL_INCLUDE_DIR}")

find_path(HAYAI_INCLUDE_DIR hayai.hpp 
  "${CMAKE_CURRENT_SOURCE_DIR}/hayai/src"
   ${CMAKE_SYSTEM_INCLUDE_DIRECTORIES}
)

message(STATUS "HAYAI_INCLUDE_DIR = ${HAYAI_INCLUDE_DIR}")
if(${HAYAI_INCLUDE_DIR} STREQUAL "HAYAI_INCLUDE_DIR-NOTFOUND")
	message(STATUS "Hayai not found, benchmark has been deactivated. "
		"You should run 'git submodule init && git submodule update' before running cmake")
else()
	include_directories(${HAYAI_INCLUDE_DIR})
	file(GLOB SOURCES_FILES *.h *cpp)
	add_executable(benchmark ${SOURCES_FILES})	
endif()

