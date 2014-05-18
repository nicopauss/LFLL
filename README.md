# LFLL - Lite Fuzzy Logic Library

---

### What is LFLL?


LFLL is a C++ fuzzy logic library designed to be fast and to use as little memory as possible. The library is heavily template based and is header-only. Moreover, **IT DOESN'T ALLOCATE**, so it can be used in embedded real-time systems. It doesn't use any third-party dependencies other than the standard library. It is also thread-safe. 

Here is a list of currently supported fuzzy logic objects:

- FIS Type:
    - Mamdani
	- Sugeno

	
- Mamdani defuzzifier method:
	- Centroid
	- Bisector
	- Mean of maximum
	- Smallest of maximum
	- Largest of maximum

	
- Sugeno defuzzifier method:
	- Weighted average
	- Weighted sum


- C-Norm:
	- Not


- T-Norm:
	- Min
	- Probabilistic product
	- Bounded difference
	- Drastic product
	- Nilpotent min
	- Einstein product
	- Hamacher product 


- S-Norm:
	- Max
	- Probabilistic sum
	- Bounded sum
	- Drastic sum
	- Nilpotent max
	- Einstein sum
	- Hamacher sum 


- Terms:
	- Trapezoid
	- Triangle
	- Rectangle
	- Bell
	- Gaussian
	- Gaussian product
	- LRamp
	- RRamp
	- SShape
	- ZShape
	- Pi-Shape
	- Sigmoid
	- Sigmoid difference
	- Sigmoid product
	- Accumulated
	- Singleton
	- Boolean
	- Function
	- Functor



### How to use LFLL?

LFLL uses a syntax close to Matlab/Octave FIS.

The easiest way is to use `python/LFLLFisImporter.py` to convert Matlab/Octave FIS into LFLL code. `python/LFLLFisImporter.py` is compatible with Python 2 and Python 3.

There are also some examples in the corresponding directory.

The only directory you need for an external project is `lfll`. `FindLFLL.cmake` is also available for external CMake projects.

### Configure LFLL

LFLL can be configurated by modifying `lfll/LFLLConfig.h` or by defining the corresponding macros in your toolchain:

|  Macro  |   Description  |  Default value  |  
|:--------|:---------------|:----------------|
| LFLL_USE_DOUBLE_SCALAR | Use double instead of float for the scalar type. Not really useful and slower | Not defined |    
| LFLL_CUSTOM_SCALAR | Define a custom-type scalar | Not defined |  
| LFLL_CUSTOM_SCALAR_NAMESPACE |  Define a custom scalar namespace for the math operations | Not defined |
| LFLL_NAMESPACE | Use a global namespace | Not defined |

For more details, see `lfll/LFLLConfig.h`.


### Compile LFLL

LFLL itself is a header-only library, so it doesn't require to be compiled directly. 
Nevertheless, the project uses CMake to compile examples, benchmark and unit tests. 
CMake is also used to install the library into the appropriate directories.

If you want to try LFLL you can compile it using the following commands.
[OPTIONS] refers to one or more of the following values:

|  Option  |   Description  |  Default value  |  
|:---------|:---------------|:----------------|
| -DSTRICT_MODE | Enable every warnings and treat warnings as errors | OFF |    
| -DDONT_BUILD_TESTS | Don't build unit tests | OFF |  
| -DDONT_BUILD_EXAMPLES |  Don't build examples | OFF |
| -DDONT_BUILD_BENCHMARKS | Don't build benchmarks | OFF |


For Linux:
```sh
$ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
$ cd LFLL # get into cloned repo
$ git submodule init # init submodules
$ git submodule update # get hayai
$ mkdir build # create a build directory
$ cd build # get into build directory
$ cmake [OPTIONS] .. # replace options and add commands if you want to
$ make # compile examples, benchmark and unit tests
$ make install # install library
```

For Mac:
```sh
$ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
$ cd LFLL # get into cloned repo
$ git submodule init # init submodules
$ git submodule update # get hayai
$ mkdir build # create a build directory
$ cd build # get into build directory
$ cmake -G"Unix Makefiles" [OPTIONS] .. # replace options and add commands if you want to
$ make # compile examples, benchmark and unit tests
$ make install # install library
```

For Windows, use VisualStudio command prompt or Cygwin:
```sh
$ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
$ cd LFLL # get into cloned repo
$ git submodule init # init submodules
$ git submodule update # get hayai
$ mkdir build # create a build directory
$ cd build # get into build directory
$ cmake -G"NMake Makefiles" [OPTIONS] .. # replace options and add commands if you want to
$ nmake # compile examples, benchmark and unit tests
$ nmake install # install library
```


You can then run the examples, benchmark and unit tests:
```sh
$ examples/mamdani/example_mamdani # mamdani example
$ examples/sugeno/example_sugeno # sugeno example
$ examples/fixedpt/example_fixedpt # fixed-point numeric example
$ examples/openmp/example_openmp # openmp example
$ benchmarks/allterms/benchmarks_allterms # allterms benchmark
$ benchmarks/fuzzylite/benchmarks_fuzzylite # fuzzylite benchmark
$ tests/tests # unit tests
```

### Documentation
LFLL is documented using [Doxygen](http://www.doxygen.org). In the library's root directory, run `doxygen`. The documentation will be available in `doc/html/index.html`.


### Benchmarks

The benchmarks are done with a Core i7 2.2Ghz with GCC 4.8.2 with [Hayai](https://github.com/nicopauss/hayai).

```
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
```

Sugeno is way faster than Mamdani. 
One iteration correponds to an entire circle fuzzification->rules->defuzzification.

LFLL is faster than [Fuzzylite](http://www.fuzzylite.com), around 3.8 times faster for Mamdani and 58.4 times for Sugeno.

```
[==========] Running 4 benchmarks.
[ RUN      ] MamdaniFixture.Fuzzylite (20 runs, 100 iterations per run)
[     DONE ] MamdaniFixture.Fuzzylite (217.866291 ms)
[   RUNS   ]        Average time: 10893.315 us
                         Fastest: 10402.406 us (-490.909 us / -4.507 %)
                         Slowest: 14480.123 us (+3586.808 us / +32.927 %)

             Average performance: 91.79942 runs/s
                Best performance: 96.13161 runs/s (+4.33218 runs/s / +4.71918 %)
               Worst performance: 69.06019 runs/s (-22.73924 runs/s / -24.77057 %)
[ITERATIONS]        Average time: 108.933 us
                         Fastest: 104.024 us (-4.909 us / -0.000 %)
                         Slowest: 144.801 us (+35.868 us / +0.000 %)

             Average performance: 9179.94239 iterations/s
                Best performance: 9613.16065 iterations/s (+433.21826 iterations/s / +4.71918 %)
               Worst performance: 6906.01869 iterations/s (-2273.92370 iterations/s / -24.77057 %)
[ RUN      ] SugenoFixture.Fuzzylite (20 runs, 10000 iterations per run)
[     DONE ] SugenoFixture.Fuzzylite (1098.741110 ms)
[   RUNS   ]        Average time: 54937.056 us
                         Fastest: 53470.978 us (-1466.077 us / -2.669 %)
                         Slowest: 57493.064 us (+2556.008 us / +4.653 %)

             Average performance: 18.20265 runs/s
                Best performance: 18.70173 runs/s (+0.49908 runs/s / +2.74182 %)
               Worst performance: 17.39340 runs/s (-0.80925 runs/s / -4.44577 %)
[ITERATIONS]        Average time: 5.494 us
                         Fastest: 5.347 us (-0.147 us / -0.000 %)
                         Slowest: 5.749 us (+0.256 us / +0.000 %)

             Average performance: 182026.50122 iterations/s
                Best performance: 187017.33864 iterations/s (+4990.83742 iterations/s / +2.74182 %)
               Worst performance: 173934.02446 iterations/s (-8092.47676 iterations/s / -4.44577 %)
[ RUN      ] MamdaniFixture.LFLL (20 runs, 100 iterations per run)
[     DONE ] MamdaniFixture.LFLL (57.867087 ms)
[   RUNS   ]        Average time: 2893.354 us
                         Fastest: 2779.036 us (-114.318 us / -3.951 %)
                         Slowest: 3080.603 us (+187.249 us / +6.472 %)

             Average performance: 345.61961 runs/s
                Best performance: 359.83701 runs/s (+14.21740 runs/s / +4.11360 %)
               Worst performance: 324.61177 runs/s (-21.00784 runs/s / -6.07831 %)
[ITERATIONS]        Average time: 28.934 us
                         Fastest: 27.790 us (-1.143 us / -0.000 %)
                         Slowest: 30.806 us (+1.872 us / +0.000 %)

             Average performance: 34561.96093 iterations/s
                Best performance: 35983.70082 iterations/s (+1421.73989 iterations/s / +4.11360 %)
               Worst performance: 32461.17724 iterations/s (-2100.78369 iterations/s / -6.07831 %)
[ RUN      ] SugenoFixture.LFLL (20 runs, 10000 iterations per run)
[     DONE ] SugenoFixture.LFLL (18.842513 ms)
[   RUNS   ]        Average time: 942.126 us
                         Fastest: 900.390 us (-41.736 us / -4.430 %)
                         Slowest: 1013.311 us (+71.185 us / +7.556 %)

             Average performance: 1061.42954 runs/s
                Best performance: 1110.62984 runs/s (+49.20029 runs/s / +4.63529 %)
               Worst performance: 986.86386 runs/s (-74.56569 runs/s / -7.02502 %)
[ITERATIONS]        Average time: 0.094 us
                         Fastest: 0.090 us (-0.004 us / -0.000 %)
                         Slowest: 0.101 us (+0.007 us / +0.000 %)

             Average performance: 10614295.44987 iterations/s
                Best performance: 11106298.38181 iterations/s (+492002.93194 iterations/s / +4.63529 %)
               Worst performance: 9868638.55223 iterations/s (-745656.89764 iterations/s / -7.02502 %)
[==========] Ran 4 benchmarks.
```


### Supported Platforms

LFLL is tested with the following compilers:

* gcc 4.8.2
* llvm-gcc 4.2.1
* clang 3.0
* vc++ 2012
* vc++ 2010


[![Build Status](https://travis-ci.org/nicopauss/LFLL.png?branch=master)](https://travis-ci.org/nicopauss/LFLL)
