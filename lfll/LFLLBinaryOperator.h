#ifndef LFLLBINARYOPERATOR_H
#define LFLLBINARYOPERATOR_H

#include "LFLLDefinitions.h"

LFLL_BEGIN_NAMESPACE

/**
 * A binary operator.
 */
struct LFLLBinaryOperator
{
    virtual dom operator()(dom val1, dom val2) const = 0;
};

LFLL_END_NAMESPACE

#endif //LFLLBINARYOPERATOR_H
