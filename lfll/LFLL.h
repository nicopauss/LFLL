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

/** @mainpage
  *
  *  ### What is LFLL?
  *  
  *  
  *  LFLL is a C++ fuzzy logic library designed to be fast and to use as little memory as possible. The library is heavily template based and is header-only. Moreover, **IT DOESN'T ALLOCATE**, so it can be used in embedded real-time systems. It doesn't use any third-party dependencies other than the standard library. It is also thread-safe. 
  *  
  *  Here is a list of currently supported fuzzy logic objects:
  *  
  *  - FIS Type:
  *      - Mamdani
  *      - Sugeno
  *  
  *      
  *  - Mamdani defuzzifier method:
  *      - Centroid
  *      - Bisector
  *      - Mean of maximum
  *      - Smallest of maximum
  *      - Largest of maximum
  *  
  *      
  *  - Sugeno defuzzifier method:
  *      - Weighted average
  *      - Weighted sum
  *  
  *  
  *  - C-Norm:
  *      - Not
  *  
  *  
  *  - T-Norm:
  *      - Min
  *      - Probabilistic product
  *      - Bounded difference
  *      - Drastic product
  *      - Nilpotent min
  *      - Einstein product
  *      - Hamacher product 
  *  
  *  
  *  - S-Norm:
  *      - Max
  *      - Probabilistic sum
  *      - Bounded sum
  *      - Drastic sum
  *      - Nilpotent max
  *      - Einstein sum
  *      - Hamacher sum 
  *  
  *  
  *  - Terms:
  *      - Trapezoid
  *      - Triangle
  *      - Rectangle
  *      - Bell
  *      - Gaussian
  *      - Gaussian product
  *      - LRamp
  *      - RRamp
  *      - SShape
  *      - ZShape
  *      - Pi-Shape
  *      - Sigmoid
  *      - Sigmoid difference
  *      - Sigmoid product
  *      - Accumulated
  *      - Singleton
  *      - Boolean
  *      - Function
  *      - Functor
  *  
  *  
  *  
  *  ### How to use LFLL?
  *  
  *  LFLL uses a syntax close to Matlab/Octave FIS.
  *  
  *  The easiest way is to use `python/LFLLFisImporter.py` to convert Matlab/Octave FIS into LFLL code. `python/LFLLFisImporter.py` is compatible with Python 2 and Python 3.
  *  
  *  There are also some examples in the corresponding directory.
  *  
  *  The only directory you need for an external project is `lfll`. `FindLFLL.cmake` is also available for external CMake projects.
  *  
  *  ### Configure LFLL
  *  
  *  LFLL can be configurated by modifying `lfll/LFLLConfig.h` or by defining the corresponding macros in your toolchain:
  *  
  *  |  Macro  |   Description  |  Default value  |  
  *  |:--------|:---------------|:----------------|
  *  | LFLL_USE_DOUBLE_SCALAR | Use double instead of float for the scalar type. Not really useful and slower. | Not defined |    
  *  | LFLL_CUSTOM_SCALAR | Define a custom-type scalar. | Not defined |  
  *  | LFLL_CUSTOM_SCALAR_NAMESPACE |  Define a custom scalar namespace for the math operations. | Not defined |
  *  | LFLL_USE_NAMESPACE | Use a global namespace. | Not defined |
  *  | LFLL_NAMESPACE_NAME | Namespace name if activated. | lfll | 
  *  
  *  For more details, see `lfll/LFLLConfig.h`.
  *  
  *  
  *  ### Compile LFLL
  *  
  *  LFLL itself is a header-only library, so it doesn't require to be compiled directly. Nevertheless, the project uses CMake to compile examples, benchmark and unit tests. CMake is also used to install the library into the appropriate directories.
  *  
  *  If you want to try LFLL you can compile it using the following commands.
  *  
  *  For Linux:
  *  ~~~{.py}
     $ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
     $ cd LFLL # get into cloned repo
     $ mkdir build # create a build directory
     $ cd build # get into build directory
     $ cmake .. # add commands if you want to
     $ make # compile examples, benchmark and unit tests
     $ make install # install library
     ~~~
  *  
  *  For Mac:
  *  ~~~{.py}
     $ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
     $ cd LFLL # get into cloned repo
     $ mkdir build # create a build directory
     $ cd build # get into build directory
     $ cmake -G"Unix Makefiles" .. # add commands if you want to
     $ make # compile examples, benchmark and unit tests
     $ make install # install library
     ~~~
  *  
  *  For Windows, use VisualStudio command prompt or Cygwin:
  *  ~~~{.py}
     $ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
     $ cd LFLL # get into cloned repo
     $ mkdir build # create a build directory
     $ cd build # get into build directory
     $ cmake -G"NMake Makefiles" .. # add commands if you want to
     $ nmake # compile examples, benchmark and unit tests
     $ nmake install # install library
     ~~~
  *  
  *  
  *  You can then run the examples, benchmark and unit tests:
  *  ~~~{.py}
     $ examples/mamdani/example_mamdani # mamdani example
     $ examples/sugeno/example_sugeno # sugeno example
     $ examples/fixedpt/example_fixedpt # fixed-point numeric example
     $ examples/openmp/example_openmp # openmp example
     $ benchmark/benchmark # benchmark
     $ tests/tests # unit tests
     ~~~
  *  
  * 
  * ### Benchmarks
  * 
  * The benchmarks are done with a Core i7 2.2Ghz with GCC 4.8.2 with [Hayai](https://github.com/nicopauss/hayai).
  * 
  * ~~~
    [==========] Running 2 benchmarks.
    [ RUN      ] MamdaniFixture.AllTerms (20 runs, 100 iterations per run)
    [     DONE ] MamdaniFixture.AllTerms (146.915000 ms)
    [   RUNS   ] 
              Average time: 7345.750000 us
                   Fastest: 7113.000000 us (-232.750000 us / -3.168499 %)
                   Slowest: 7623.000000 us (+277.250000 us / +3.774291 %)
                        
       Average performance: 136.133138 runs/s
          Best performance: 140.587656 runs/s (+4.454518 runs/s / +3.272178 %)
         Worst performance: 131.181949 runs/s (-4.951189 runs/s / -3.637020 %)
    [ITERATIONS] 
              Average time: 73.457500 us
                   Fastest: 71.130000 us (-2.327500 us / -3.168499 %)
                   Slowest: 76.230000 us (+2.772500 us / +3.774291 %)
                        
       Average performance: 13613.313821 iterations/s
          Best performance: 14058.765640 iterations/s (+445.451819 iterations/s / +3.272178 %)
         Worst performance: 13118.194936 iterations/s (-495.118885 iterations/s / -3.637020 %)
    [ RUN      ] SugenoFixture.AllTerms (20 runs, 10000 iterations per run)
    [     DONE ] SugenoFixture.AllTerms (37.545000 ms)
    [   RUNS   ] 
              Average time: 1877.250000 us
                   Fastest: 1822.000000 us (-55.250000 us / -2.943135 %)
                   Slowest: 2036.000000 us (+158.750000 us / +8.456519 %)
                        
       Average performance: 532.694100 runs/s
          Best performance: 548.847420 runs/s (+16.153320 runs/s / +3.032382 %)
         Worst performance: 491.159136 runs/s (-41.534965 runs/s / -7.797151 %)
    [ITERATIONS] 
              Average time: 0.187725 us
                   Fastest: 0.182200 us (-0.005525 us / -2.943135 %)
                   Slowest: 0.203600 us (+0.015875 us / +8.456519 %)
                        
       Average performance: 5326941.004128 iterations/s
          Best performance: 5488474.204171 iterations/s (+161533.200043 iterations/s / +3.032382 %)
         Worst performance: 4911591.355599 iterations/s (-415349.648529 iterations/s / -7.797151 %)
    [==========] Ran 2 benchmarks.
    ~~~
  * 
  * Sugeno is way faster than Mamdani. 
  * One iteration correponds to an entire circle fuzzification->rules->defuzzification.
  * 
  * 
  * ### Supported Platforms
  * 
  * LFLL is tested with the following compilers:
  * 
  * - gcc 4.8.2
  * - llvm-gcc 4.2.1
  * - clang 3.0
  * - vc++ 2012
  * - vc++ 2010
  * 
  */

#ifndef LFLL_H
#define LFLL_H

#define LFLL_MAJOR_VERSION 1
#define LFLL_MINOR_VERSION 0
#define LFLL_PATCH_VERSION 1
#define LFLL_VERSION "LFLL_MAJOR_VERSION.LFLL_MINOR_VERSION.LFLL_PATCH_VERSION"


#include <lfll/engine/LFLLAggregator.h>
#include <lfll/engine/LFLLArray.h>
#include <lfll/engine/LFLLConsequence.h>
#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLInputFuzzifier.h>
#include <lfll/engine/LFLLMath.h>
#include <lfll/engine/LFLLMembership.h>
#include <lfll/engine/LFLLRule.h>
#include <lfll/engine/LFLLRulesEngine.h>
#include <lfll/engine/LFLLStaticAssert.h>
#include <lfll/engine/LFLLTuple.h>
#include <lfll/mamdani/LFLLMamdaniDefuzzifier.h>
#include <lfll/norms/LFLLCNorm.h>
#include <lfll/norms/LFLLSNorm.h>
#include <lfll/norms/LFLLTNorm.h>
#include <lfll/sugeno/LFLLSugenoDefuzzifier.h>
#include <lfll/sugeno/LFLLSugenoTerms.h>
#include <lfll/terms/LFLLAccumulated.h>
#include <lfll/terms/LFLLBell.h>
#include <lfll/terms/LFLLBoolean.h>
#include <lfll/terms/LFLLFunction.h>
#include <lfll/terms/LFLLFunctor.h>
#include <lfll/terms/LFLLGaussian.h>
#include <lfll/terms/LFLLGaussianProduct.h>
#include <lfll/terms/LFLLLRamp.h>
#include <lfll/terms/LFLLPiShape.h>
#include <lfll/terms/LFLLRectangle.h>
#include <lfll/terms/LFLLRRamp.h>
#include <lfll/terms/LFLLSigmoid.h>
#include <lfll/terms/LFLLSigmoidDifference.h>
#include <lfll/terms/LFLLSigmoidProduct.h>
#include <lfll/terms/LFLLSingleton.h>
#include <lfll/terms/LFLLSShape.h>
#include <lfll/terms/LFLLTrapezoid.h>
#include <lfll/terms/LFLLTriangle.h>
#include <lfll/terms/LFLLZShape.h>

#endif // LFLL_H
