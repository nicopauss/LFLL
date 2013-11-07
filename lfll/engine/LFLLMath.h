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

/**
 * \brief Private namespace for LFLL math functions.
 */
namespace lfll_math {

    /**
      * \brief Get relative value between minVal and maxVal
      * \param val Scalar value between 0.0 and 1.0
      * \param minVal Min value
      * \param maxVal Max value
      * \return (val * (maxVal - minVal)) + minVal
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
    * \brief Test if scalar _a_ is less than scalar _b_ with given _precision_
    */
    inline bool isLessThan(const scalar a, const scalar b,
                           const scalar precision = SCALAR_DIFF_PRECISION) {
        return a < (b - precision);
    }

    /**
    * \brief Test if scalar _a_ is greater than scalar _b_ with given _precision_
    */
    inline bool isGreaterThan(const scalar a, const scalar b,
                              const scalar precision = SCALAR_DIFF_PRECISION) {
        return a > (b + precision);
    }

    /**
    * \brief Test if scalar _a_ is equal to scalar _b_ with given _precision_
    */
    inline bool isEqualTo(const scalar a, const scalar b,
                          const scalar precision = SCALAR_DIFF_PRECISION) {
        return (a >= (b - precision)) && (a <= (b + precision));
    }

    /**
    * \brief Test if scalar _a_ is less or equal to scalar _b_ with given _precision_
    */
    inline bool isLessOrEqualTo(const scalar a, const scalar b,
                                const scalar precision = SCALAR_DIFF_PRECISION) {
        return a <= (b + precision);
    }

    /**
    * \brief Test if scalar _a_ is less or equal to scalar _b_ with given _precision_
    */
    inline bool isGreaterOrEqualTo(const scalar a, const scalar b,
                                   const scalar precision = SCALAR_DIFF_PRECISION) {
        return a >= (b - precision);
    }

    /**
     * \brief Max(a, b)
     */
    inline scalar max(const scalar a, const scalar b)
    {
        return (a < b) ? b : a;
    }

    /**
     * \brief Min(a, b)
     */
    inline scalar min(const scalar a, const scalar b)
    {
        return (a < b) ? a : b;
    }
    
#ifdef LFLL_CUSTOM_SCALAR_NAMESPACE
	using LFLL_CUSTOM_SCALAR_NAMESPACE::abs;
	using LFLL_CUSTOM_SCALAR_NAMESPACE::pow;
	using LFLL_CUSTOM_SCALAR_NAMESPACE::exp;
#else
	using std::abs;
	using std::pow;
	using std::exp;
#endif    


}

LFLL_END_NAMESPACE


#endif //LFLLMATH_H
