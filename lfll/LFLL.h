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
  * LFLL is a fuzzy logic library designed to be fast and to use as
  * little memory as possible.
  * This library doesn't use any external dependency and is header-only.
  * Moreover, IT DOESN'T ALLOCATE, so it can be used in embedded real-time
  * systems.
  *
  * Here is a list of currently supported fuzzy logic objects:
  *
  * - FIS model:
  * 	- Zero-order and first-order sugeno FIS
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
  */

#ifndef LFLL_H
#define LFLL_H

#define LFLL_MAJOR_VERSION 0
#define LFLL_MINOR_VERSION 1
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
