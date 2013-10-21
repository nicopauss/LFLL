/*
The MIT License (MIT)

Copyright (c) 2013 Nicolas Pauss

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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
    int nbProcess = 1000000;
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

