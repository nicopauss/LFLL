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
  * The benchmarks are done with a Core i7 2.0Ghz with Visual Studio 2012 with [Hayai](https://github.com/nicopauss/hayai).
  * 
  * ~~~
    [==========] Running 2 benchmarks.
    [ RUN      ] MamdaniFixture.AllTerms (20 runs, 100 iterations per run)
    [     DONE ] MamdaniFixture.AllTerms (224.517495 ms)
    [   RUNS   ]
              Average time: 11225.874750 us
                   Fastest: 10871.695000 us (-354.179750 us / -3.155030 %)
                   Slowest: 11780.492000 us (+554.617250 us / +4.940526 %)
    
       Average performance: 89.079918 runs/s
          Best performance: 91.981977 runs/s (+2.902059 runs/s / +3.257815 %)
         Worst performance: 84.886098 runs/s (-4.193820 runs/s / -4.707929 %)
    [ITERATIONS]
              Average time: 112.258747 us
                   Fastest: 108.716950 us (-3.541797 us / -3.155030 %)
                   Slowest: 117.804920 us (+5.546173 us / +4.940526 %)
    
       Average performance: 8907.991780 iterations/s
          Best performance: 9198.197705 iterations/s (+290.205925 iterations/s / +3.257815 %)
         Worst performance: 8488.609814 iterations/s (-419.381967 iterations/s / -4.707929 %)
    [ RUN      ] SugenoFixture.AllTerms (20 runs, 10000 iterations per run)
    [     DONE ] SugenoFixture.AllTerms (81.332961 ms)
    [   RUNS   ]
              Average time: 4066.648050 us
                   Fastest: 3888.173000 us (-178.475050 us / -4.388751 %)
                   Slowest: 4217.618000 us (+150.969950 us / +3.712393 %)
    
       Average performance: 245.902765 runs/s
          Best performance: 257.190202 runs/s (+11.287437 runs/s / +4.590203 %)
         Worst performance: 237.100657 runs/s (-8.802108 runs/s / -3.579507 %)
    [ITERATIONS]
              Average time: 0.406665 us
                   Fastest: 0.388817 us (-0.017848 us / -4.388751 %)
                   Slowest: 0.421762 us (+0.015097 us / +3.712393 %)
    
       Average performance: 2459027.650549 iterations/s
          Best performance: 2571902.021849 iterations/s (+112874.371301 iterations/s / +4.590203 %)
         Worst performance: 2371006.572904 iterations/s (-88021.077644 iterations/s / -3.579507 %)
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
#define LFLL_PATCH_VERSION 0
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
