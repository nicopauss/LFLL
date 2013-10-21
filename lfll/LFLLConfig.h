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
#ifndef LFLLCONFIG_H
#define LFLLCONFIG_H

/** @mainpage
  *
  * ElectronicHorizonLFLL is a fuzzy logic library designed to be fast
  * and to use as little memory as possible.
  * This library don't use any external dependency and it is only constituted
  * in headers.
  * Moreover, IT DOESN'T ALLOCATE, so it can be used in real-time systems.
  *
  * Here is a list of currently supported fuzzy logic objects:
  *
  * - FIS model:
  * 	- Zero-order sugeno FIS
  * - LFLL Term Types:
  * 	- SShape
  * 	- ZShape
  * 	- PiShape
  * 	- Rectangular
  * 	- Trapezoid
  * 	- Triangle
  * 	- Singleton
  * 	- Boolean
  * - LFLL Operator:
  * 	- Min (min(a, b))
  * 	- Max (max(a, b))
  * 	- Complement (1-a)
  *
  *
  * It currently only supports zero-order Sugeno FIS because
  * it is the fastest. One can easily implements Mamdani FIS.
  *
  * An example is available in the solution ElectronicHorizonLFLLExample
  */


/************************************************************************/
/*
This file defines some constants used in the fuzzy library.
*/
/************************************************************************/

// Use double instead of float for the scalar type.
// Not really useful and slower.
// #define LFLL_USE_DOUBLE_SCALAR

// Use custom scalar. You can use fixed precision real type.
// #define LFLL_USE_CUSTOM_SCALAR
// typedef custom_scalar scalar

// Internal memory use, unsigned 8 bits, unsigned 16 bits or unsigned 32 bits.
// Use potentially less memory but increase approximation errors.
// Default is unsigned 32 bits.
// #define LFLL_USE_U8_DOM
// #define LFLL_USE_U16_DOM
// #define LFLL_USE_U32_DOM

// Disable optimisations. Since there is no optimisations at this time,
// this is useless
// #define LFLL_NOT_USE_OPTIMISATIONS

// Use namespace
// #define LFLL_USE_NAMESPACE

// Namespace name if activated
// #define LFLL_NAMESPACE_NAME ehfl


#endif //LFLLCONFIG_H
