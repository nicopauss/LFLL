/************************************************************************/
/** @mainpage
* Here is an example of how to use the library ElectronicHorizonLFLL. \n
*
* You can activate OpenMP to get a better speed.
*
* To compile this example, undefine every preprocessor macros in LFLLConfig.h.
*/
/************************************************************************/

#include <iostream>
#include "ExampleLFLLEngine.h"

#ifdef _OPENMP
#include <omp.h>
#else
#include <ctime>
double omp_get_wtime()
{
    return (double)clock() / ((double)CLOCKS_PER_SEC);
}

#endif



scalar processValueWithLoop(scalar val1, scalar val2, int nbProcess);

int main(int argc, char* argv[])
{
    // Initialse variables
    int nbProcess = 1000;
    scalar val1 = 0.2f;
    scalar val2 = 0.3f;
    scalar result;

    // Measure process
    double start = omp_get_wtime();
    result = processValueWithLoop(val1, val2, nbProcess);
    double end = omp_get_wtime();
    double elapsed_secs = end - start;

    // Output result
    std::cout << "LFLLEngine: Processed " << nbProcess <<
        " times (" << val1 << ", " << val2 <<
        ") = " << result << " in " << elapsed_secs <<
        " s" << std::endl;

    return 0;
}

scalar processValueWithLoop(scalar val1, scalar val2, int nbProcess)
{
    scalar result;

#pragma omp parallel for shared(result)
    for (int i = 0 ; i < nbProcess ; ++i) {
        result = ExampleLFLLEngine::process(val1, val2);
    }

    return result;
}

