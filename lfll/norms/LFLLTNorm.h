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
#ifndef LFLLTNORM_H
#define LFLLTNORM_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>

LFLL_BEGIN_NAMESPACE

/**
  * Standard min
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = min(a, b)
  * @f]
  */
struct LFLLMin
{
    inline scalar operator()(const scalar a, const scalar b) const {
        return math::min(a, b);
    }
};

/**
  * Probabilistic product
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = a * b
  * @f]
  */
struct LFLLProbabilisticProduct
{
    inline scalar operator()(const scalar a, const scalar b) const {
        return a * b;
    }
};

/**
  * Bounded difference
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = max(0, a + b - 1)
  * @f]
  */
struct LFLLBoundedDifference
{
    inline scalar operator()(const scalar a, const scalar b) const {
        return math::max(ZERO_SCALAR, a + b - ONE_SCALAR);
    }
};

/**
  * Drastic product
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = \left \{
   \begin{array}{cc}
     a, & b = 1 \\
     b, & a = 1 \\
     0, & otherwise \\
   \end{array}
\right \}
  * @f]
  */
struct LFLLDrasticProduct
{
    inline scalar operator()(const scalar a, const scalar b) const {
        if (math::isEqualTo(math::max(a, b), ONE_SCALAR)) {
            return math::min(a, b);
        }
        return ZERO_SCALAR;
    }
};

/**
  * Nilpotent min
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = \left \{
   \begin{array}{cc}
     min(a, b), & a + b > 1 \\
     0, & otherwise \\
   \end{array}
\right \}
  * @f]
  */
struct LFLLNilpotentMin
{
    inline scalar operator()(const scalar a, const scalar b) const {
        if (math::isGreaterThan(a + b, ONE_SCALAR)) {
            return math::min(a, b);
        }
        return ZERO_SCALAR;
    }
};

/**
  * Einstein product
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = (a * b) / (2 - (a + b - a * b))
  * @f]
  */
struct LFLLEinsteinProduct
{
    inline scalar operator()(const scalar a, const scalar b) const {
        const scalar prod = a * b;
        return prod / (TWO_SCALAR - (a + b - prod));
    }
};

/**
  * Hamacher product
  * 
  * @f[
\renewcommand{\arraystretch}{2.25}
a:[0,1], b:[0,1] \rightarrow  f(a, b) = \left \{
   \begin{array}{cc}
     0, & a = b = 0 \\
     (a * b) / (a + b - a * b), & otherwise \\
   \end{array}
\right \}
  * @f]
  */
struct LFLLHamacherProduct
{
    inline scalar operator()(const scalar a, const scalar b) const {
        if (math::isEqualTo(a, ZERO_SCALAR) &&
        	math::isEqualTo(b, ZERO_SCALAR))
        {
        	return ZERO_SCALAR;
        }
        const scalar prod = a * b;
        return prod / (a + b - prod);
    }
};

LFLL_END_NAMESPACE


#endif //LFLLTNORM_H
