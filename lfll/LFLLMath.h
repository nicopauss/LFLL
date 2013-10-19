#ifndef LFLLMATH_H
#define LFLLMATH_H

#include <cmath>

#include "LFLLDefinitions.h"

LFLL_BEGIN_NAMESPACE

namespace math {

    /**
      * Get rounded value
      * @param sVal Scalar value between 0.0 and 1.0
      * @param minVal Unsigned min value
      * @param maxVal Unsigned max value
      * @return round(sVal * (maxVal - minVal))
      */
    template<typename INTT>
    inline INTT sround(const scalar sVal, const INTT minVal, const INTT maxVal)
    {
        if (sVal >= ONE_SCALAR) {
            return maxVal;
        } else if (sVal <= ZERO_SCALAR) {
            return minVal;
        } else {
            const scalar diffVal = scalar(maxVal - minVal);
            const INTT result = static_cast<INTT>((sVal * diffVal)
                + HALF_SCALAR) - minVal;
            return result;
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
