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
#ifndef LFLLMATH_H
#define LFLLMATH_H

#include <cmath>

#include <lfll/engine/LFLLDefinitions.h>

LFLL_BEGIN_NAMESPACE

namespace math {

    /**
      * Get relative value between minVal and maxVal
      * @param val Scalar value between 0.0 and 1.0
      * @param minVal Min value
      * @param maxVal Max value
      * @return (val * (maxVal - minVal)) + minVal
      */
    inline scalar srel(const scalar val, const scalar minVal, const scalar maxVal)
    {
        if (val >= ONE_SCALAR) {
            return maxVal;
        } else if (val <= ZERO_SCALAR) {
            return minVal;
        } else {
            return val * (maxVal - minVal) + minVal;
        }
    }

    /**
    * Test if scalar a is less than scalar b with given precision
    */
    inline bool isLessThan(const scalar a, const scalar b,
                           const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a - precision) < b;
    }

    /**
    * Test if scalar a is greater than scalar b with given precision
    */
    inline bool isGreaterThan(const scalar a, const scalar b,
                              const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a + precision) > b;
    }

    /**
    * Test if scalar a is equal to scalar b with given precision
    */
    inline bool isEqualTo(const scalar a, const scalar b,
                          const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a - precision) <= b && (a + precision) >= b;
    }

    /**
    * Test if scalar a is less or equal to scalar b with given precision
    */
    inline bool isLessOrEqualTo(const scalar a, const scalar b,
                                const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a - precision) <= b;
    }

    /**
    * Test if scalar a is less or equal to scalar b with given precision
    */
    inline bool isGreaterOrEqualTo(const scalar a, const scalar b,
                                   const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a + precision) >= b;
    }

    /**
      * Max
      */
    inline scalar max(const scalar a, const scalar b)
    {
        return (a < b) ? b : a;
    }

    /**
      * Min
      */
    inline scalar min(const scalar a, const scalar b)
    {
        return (a < b) ? a : b;
    }

}

LFLL_END_NAMESPACE


#endif //LFLLMATH_H
