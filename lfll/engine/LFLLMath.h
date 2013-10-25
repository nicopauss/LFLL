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

#if defined(LFLL_USE_SCALAR_DOM)
    /**
      * Get rounded value
      * @param sVal Scalar value between 0.0 and 1.0
      * @param minVal Unsigned min value
      * @param maxVal Unsigned max value
      * @return round(sVal * (maxVal - minVal)) + minVal
      */
    template<typename T>
    inline T sround(const scalar sVal, const T minVal, const T maxVal)
    {
        if (sVal >= ONE_SCALAR) {
            return maxVal;
        } else if (sVal <= ZERO_SCALAR) {
            return minVal;
        } else {
            const scalar diffVal = scalar(maxVal - minVal);
            return static_cast<T>(sVal * diffVal) + minVal;
        }
    }


    /**
    * Convert a scalar between 0.0 and 1.0 to dom
    */
    inline dom scalarToDom(const scalar val)
    {
        if (val >= ONE_SCALAR) {
            return MAX_DOM;
        } else if (val <= ZERO_SCALAR) {
            return MIN_DOM;
        }
        return static_cast<dom>(val);
    }

    /**
    * Convert a dom to a scalar between 0.0 and 1.0
    */
    inline scalar domToScalar(const dom val)
    {
        return static_cast<scalar>(val);
    }

#else //defined(LFLL_USE_SCALAR_DOM)
    /**
      * Get rounded value
      * @param sVal Scalar value between 0.0 and 1.0
      * @param minVal Unsigned min value
      * @param maxVal Unsigned max value
      * @return round(sVal * (maxVal - minVal))
      */
    template<typename T>
    inline T sround(const scalar sVal, const T minVal, const T maxVal)
    {
        if (sVal >= ONE_SCALAR) {
            return maxVal;
        } else if (sVal <= ZERO_SCALAR) {
            return minVal;
        } else {
            const scalar diffVal = scalar(maxVal - minVal);
            return static_cast<T>((sVal * diffVal)
                + HALF_SCALAR) + minVal;
        }
    }


    /**
    * Convert a scalar between 0.0 and 1.0 to dom
    */
    inline dom scalarToDom(const scalar val)
    {
        return sround<dom>(val, MIN_DOM, MAX_DOM);
    }

    /**
    * Convert a dom to a scalar between 0.0 and 1.0
    */
    inline scalar domToScalar(const dom val)
    {
        return scalar(val) / scalar(DOM_DIFF);
    }

#endif


    /**
    * Test if scalar a is less than scalar b with given precision
    */
    inline bool isLessThan(const scalar a, const scalar b, const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a - precision) < b;
    }

    /**
    * Test if scalar a is greater than scalar b with given precision
    */
    inline bool isGreaterThan(const scalar a, const scalar b, const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a + precision) > b;
    }

    /**
    * Test if scalar a is equal to scalar b with given precision
    */
    inline bool isEqualTo(const scalar a, const scalar b, const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a - precision) <= b && (a + precision) >= b;
    }

    /**
    * Test if scalar a is less or equal to scalar b with given precision
    */
    inline bool isLessOrEqualTo(const scalar a, const scalar b, const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a - precision) <= b;
    }

    /**
    * Test if scalar a is less or equal to scalar b with given precision
    */
    inline bool isGreaterOrEqualTo(const scalar a, const scalar b, const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a + precision) >= b;
    }

}

LFLL_END_NAMESPACE


#endif //LFLLMATH_H
