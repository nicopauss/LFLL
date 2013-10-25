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
  * Standard Max
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = max(a, b)
  * @f]
  */
struct LFLLMax
{
    inline scalar operator()(const scalar a, const scalar b) const {
        return math::max(a, b);
    }
};

/**
  * Probabilistic sum
  * 
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
  * Bounded sum
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = max(1, a + b)
  * @f]
  */
struct LFLLBoundedSum
{
    inline scalar operator()(const scalar a, const scalar b) const {
    	return math::max(ONE_SCALAR, a + b);
    }
};

/**
  * Normalized sum
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = (a + b) / max(1, max(a, b))
  * @f]
  */
struct LFLLNormalizedSum
{
    inline scalar operator()(const scalar a, const scalar b) const {
    	return (a + b) / math::max(ONE_SCALAR, math::max(a, b));
    }
};

/**
  * Drastic sum
  * 
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
    	if (math::isEqualTo(math::min(a, b), ZERO_SCALAR)) {
    		return math::max(a, b);
    	}
    	return ONE_SCALAR;
    }
};

/**
  * Nilpotent max
  * 
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
    	if ((a + b) < ONE_SCALAR) {
    		return math::max(a, b);
    	}
    	return ONE_SCALAR;
    }
};


/**
  * Einstein sum
  * 
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
  * Hamacher sum
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = (a + b - 2 * a * b) / (1 - a * b)
  * @f]
  */
struct LFLLHamacherSum
{
    inline scalar operator()(const scalar a, const scalar b) const {
    	const scalar prod = a * b;
    	return (a + b - (TWO_SCALAR * prod)) / (ONE_SCALAR - prod);
    }
};



LFLL_END_NAMESPACE


#endif //LFLLSNORM_H
