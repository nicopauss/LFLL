#ifndef LFLLDEFINITIONS_H
#define LFLLDEFINITIONS_H

#include "LFLLConfig.h"

#include <cstring>

#define __STDC_LIMIT_MACROS
#include <climits>

#include <stdint.h>

/************************************************************************/
/* Namespace definition */
/************************************************************************/

#ifdef LFLL_USE_NAMESPACE

#define LFLL_BEGIN_NAMESPACE namespace LFLL_NAMESPACE_NAME {
#define LFLL_END_NAMESPACE }

#else //LFLL_USE_NAMESPACE

#define LFLL_BEGIN_NAMESPACE
#define LFLL_END_NAMESPACE

#endif //LFLL_USE_NAMESPACE

LFLL_BEGIN_NAMESPACE

    /************************************************************************/
    /* Scalar */
    /************************************************************************/
#ifdef LFLL_USE_CUSTOM_SCALAR
#	ifdef LFLL_USE_FLOAT_SCALAR
#		undef LFLL_USE_FLOAT_SCALAR
#	endif
#	ifdef LFLL_USE_DOUBLE_SCALAR
#		undef LFLL_USE_FLOAT_SCALAR
#	endif

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
    /* dom */
    /************************************************************************/

#if defined(LFLL_USE_U8_DOM)

#	ifdef LFLL_USE_U16_DOM
#		undef LFLL_USE_U16_DOM
#	endif
#	ifdef LFLL_USE_U32_DOM
#		undef LFLL_USE_U32_DOM
#	endif

    typedef uint8_t dom;

#elif defined(LFLL_USE_U16_DOM)

#	ifdef LFLL_USE_U32_DOM
#		undef LFLL_USE_U32_DOM
#	endif

    typedef uint16_t dom;
#else
#	ifndef LFLL_USE_U32_DOM
#		define LFLL_USE_U32_DOM
#	endif

    typedef uint32_t dom;
#endif


    /************************************************************************/
    /* DOM Def */
    /************************************************************************/

#if defined(LFLL_USE_U8_DOM)
    const dom MAX_DOM = UINT8_MAX;
    const dom MIN_DOM = 0;
#elif defined(LFLL_USE_U16_DOM)
    const dom MAX_DOM = UINT16_MAX;
    const dom MIN_DOM = 0;
#elif defined(LFLL_USE_U32_DOM)
    const dom MAX_DOM = UINT32_MAX;
    const dom MIN_DOM = 0;
#else
#error Unknown defined dom type
#endif

    const dom DOM_DIFF = MAX_DOM - MIN_DOM;



    /************************************************************************/
    /* Scalar values */
    /************************************************************************/

    const scalar ZERO_SCALAR = scalar(0);
    const scalar ONE_SCALAR = scalar(1);
    const scalar TWO_SCALAR = scalar(2);
    const scalar HALF_SCALAR = ONE_SCALAR / TWO_SCALAR;


    const scalar SCALAR_DIFF_PRECISION = ONE_SCALAR / scalar(1e4);


LFLL_END_NAMESPACE

#endif //LFLLDEFINITIONS_H
