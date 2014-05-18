set(SOURCES_FILES

main.cpp
LFLLBenchmark.h
MamdaniAllTerms.cpp
MamdaniAllTerms.h
MamdaniBenchmark.cpp
SugenoAllTerms.cpp
SugenoAllTerms.h
SugenoBenchmark.cpp
)


add_executable(benchmarks_allterms ${SOURCES_FILES})
add_dependencies(benchmarks_allterms hayai)
if (${NEED_RT_LIB})
    target_link_libraries(benchmarks_allterms rt)
endif()