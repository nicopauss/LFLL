#ifndef LFLLUNARYOPERATOR_H
#define LFLLUNARYOPERATOR_H

#include "LFLLDefinitions.h"

LFLL_BEGIN_NAMESPACE

/**
  * Unary operator
  */
struct LFLLUnaryOperator
{
    virtual dom operator()(dom val) const = 0;
};

LFLL_END_NAMESPACE


#endif //LFLLUNARYOPERATOR_H
