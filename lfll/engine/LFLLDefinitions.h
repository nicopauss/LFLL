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
#ifndef LFLLDEFINITIONS_H
#define LFLLDEFINITIONS_H

#include <cstring>

#include <limits>
#include <algorithm>

#include <lfll/LFLLConfig.h>

/************************************************************************/
/* Namespace definition */
/************************************************************************/

#ifdef LFLL_USE_NAMESPACE

#ifndef LFLL_NAMESPACE_NAME
#define LFLL_NAMESPACE_NAME lfll
#endif

#define LFLL_BEGIN_NAMESPACE namespace LFLL_NAMESPACE_NAME {
#define LFLL_END_NAMESPACE }
#define LFLL_USING_NAMESPACE using namespace LFLL_NAMESPACE_NAME;

#else //LFLL_USE_NAMESPACE

#ifdef LFLL_NAMESPACE_NAME
#undef LFLL_NAMESPACE_NAME
#endif

#define LFLL_NAMESPACE_NAME
#define LFLL_BEGIN_NAMESPACE
#define LFLL_END_NAMESPACE
#define LFLL_USING_NAMESPACE

#endif //LFLL_USE_NAMESPACE

LFLL_BEGIN_NAMESPACE

/************************************************************************/
/* Scalar */
/************************************************************************/
#ifdef LFLL_CUSTOM_SCALAR
#	ifdef LFLL_USE_FLOAT_SCALAR
#		undef LFLL_USE_FLOAT_SCALAR
#	endif
#	ifdef LFLL_USE_DOUBLE_SCALAR
#		undef LFLL_USE_FLOAT_SCALAR
#	endif
	
	typedef LFLL_CUSTOM_SCALAR scalar;
	
#elif defined(LFLL_USE_DOUBLE_SCALAR)

#	ifdef LFLL_USE_FLOAT_SCALAR
#		undef LFLL_USE_FLOAT_SCALAR
#	endif

    typedef double scalar;

#else //LFLL_USE_FLOAT_SCALAR

#	ifndef LFLL_USE_FLOAT_SCALAR
#		define LFLL_USE_FLOAT_SCALAR
#	endif

    typedef float scalar;
#endif // LFLL_USE_DOUBLE_SCALAR

/************************************************************************/
/* Scalar values */
/************************************************************************/

const scalar ZERO_SCALAR = scalar(0);
const scalar ONE_SCALAR = scalar(1);
const scalar TWO_SCALAR = scalar(2);
const scalar HALF_SCALAR = ONE_SCALAR / TWO_SCALAR;
const scalar SCALAR_DIFF_PRECISION = ONE_SCALAR / scalar(1e4);

/************************************************************************/
/* Unisgned int */
/************************************************************************/

typedef int lfll_int;
typedef unsigned int lfll_uint;

LFLL_END_NAMESPACE

#endif //LFLLDEFINITIONS_H
