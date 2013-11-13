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
#ifndef LFLLSNORM_H
#define LFLLSNORM_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief S-Norm - Standard Max
  * 
  * Define the following function:
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = max(a, b)
  * @f]
  */
struct LFLLMax
{
    inline scalar operator()(const scalar a, const scalar b) const {
        return lfll_math::max(a, b);
    }
};

/**
  * \brief S-Norm - Probabilistic sum
  * 
  * Define the following function:
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = a + b - (a * b)
  * @f]
  */
struct LFLLProbabilisticSum
{
    inline scalar operator()(const scalar a, const scalar b) const {
        return a + b - (a * b);
    }
};

/**
  * \brief S-Norm - Bounded sum
  * 
  * Define the following function:
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = max(1, a + b)
  * @f]
  */
struct LFLLBoundedSum
{
    inline scalar operator()(const scalar a, const scalar b) const {
    	return lfll_math::min(ONE_SCALAR, a + b);
    }
};

/**
  * \brief S-Norm - Drastic sum
  * 
  * Define the following function:
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = \left \{
   \begin{array}{cc}
     b, & a = 0 \\
     a, & b = 0 \\
     1, & otherwise \\
   \end{array}
\right \}
  * @f]
  */
struct LFLLDrasticSum
{
    inline scalar operator()(const scalar a, const scalar b) const {
    	if (lfll_math::isEqualTo(lfll_math::min(a, b), ZERO_SCALAR)) {
    		return lfll_math::max(a, b);
    	}
    	return ONE_SCALAR;
    }
};

/**
  * \brief S-Norm - Nilpotent max
  * 
  * Define the following function:
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = \left \{
   \begin{array}{cc}
     max(a, b), & a + b < 1 \\
     1, & otherwise \\
   \end{array}
\right \}
  * @f]
  */
struct LFLLNilpotentMax
{
    inline scalar operator()(const scalar a, const scalar b) const {
    	if (lfll_math::isLessThan(a + b, ONE_SCALAR)) {
    		return lfll_math::max(a, b);
    	}
    	return ONE_SCALAR;
    }
};


/**
  * \brief S-Norm - Einstein sum
  * 
  * Define the following function:
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = (a + b) / (1 + (a * b))
  * @f]
  */
struct LFLLEinsteinSum
{
    inline scalar operator()(const scalar a, const scalar b) const {
    	return (a + b) / (ONE_SCALAR + (a * b));
    }
};

/**
  * \brief S-Norm - Hamacher sum
  *
  * Define the following function:
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = (a + b - 2 * a * b) / (1 - a * b)
  * @f]
  */
struct LFLLHamacherSum
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4723) // Warning for division by 0
#endif // _MSC_VER
    inline scalar operator()(const scalar a, const scalar b) const {
    	const scalar prod = a * b;
        if (lfll_math::isEqualTo(prod, ONE_SCALAR)) {
            return ONE_SCALAR;
        }
    	return (a + b - (TWO_SCALAR * prod)) / (ONE_SCALAR - prod);
    }
#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER
};



LFLL_END_NAMESPACE


#endif //LFLLSNORM_H
