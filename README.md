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
| LFLL_USE_DOUBLE_SCALAR | Use double instead of float for the scalar type. Not really useful and slower. | Not defined |    
| LFLL_CUSTOM_SCALAR | Define a custom-type scalar. | Not defined |  
| LFLL_CUSTOM_SCALAR_NAMESPACE |  Define a custom scalar namespace for the math operations. | Not defined |
| LFLL_USE_NAMESPACE | Use a global namespace. | Not defined |
| LFLL_NAMESPACE_NAME | Namespace name if activated. | lfll | 

For more details, see `lfll/LFLLConfig.h`.


### Compile LFLL

LFLL itself is a header-only library, so it doesn't require to be compiled directly. Nevertheless, the project uses CMake to compile examples, benchmark and unit tests. CMake is also used to install the library into the appropriate directories.

If you want to try LFLL you can compile it using the following commands.

For Linux:
```
$ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
$ cd LFLL # get into cloned repo
$ mkdir build # create a build directory
$ cd build # get into build directory
$ cmake .. # add commands if you want to
$ make # compile examples, benchmark and unit tests
$ make install # install library
```

For Mac:
```
$ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
$ cd LFLL # get into cloned repo
$ mkdir build # create a build directory
$ cd build # get into build directory
$ cmake -G"Unix Makefiles" .. # add commands if you want to
$ make # compile examples, benchmark and unit tests
$ make install # install library
```

For Windows, use VisualStudio command prompt or Cygwin:
```
$ git clone https://github.com/nicopauss/LFLL.git LFLL # clone LFLL
$ cd LFLL # get into cloned repo
$ mkdir build # create a build directory
$ cd build # get into build directory
$ cmake -G"NMake Makefiles" .. # add commands if you want to
$ nmake # compile examples, benchmark and unit tests
$ nmake install # install library
```


You can then run the examples, benchmark and unit tests:
```
$ examples/mamdani/example_mamdani # mamdani example
$ examples/sugeno/example_sugeno # sugeno example
$ examples/fixedpt/example_fixedpt # fixed-point numeric example
$ examples/openmp/example_openmp # openmp example
$ benchmark/benchmark # benchmark
$ tests/tests # unit tests
```

### Documentation
LFLL is documented using [Doxygen](http://www.doxygen.org). In the library's root directory, run `doxygen`. The documentation will be available in `doc/html/index.html`.

### Supported Platforms
LFLL is tested with the following compilers:
* gcc 4.8
* llvm-gcc 4.2
* clang 3.3
* vc++ 11
* vc++ 10
