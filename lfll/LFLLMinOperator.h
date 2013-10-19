#ifndef LFLLMINOPERATOR_H
#define LFLLMINOPERATOR_H

#include "LFLLBinaryOperator.h"

LFLL_BEGIN_NAMESPACE

/**
  * Standard min operator
  */
struct LFLLMinOperator : public LFLLBinaryOperator
{
    inline dom operator()(dom val1, dom val2) const {
        return (val1 < val2) ? val1 : val2;
    }
};

LFLL_END_NAMESPACE


#endif //LFLLMINOPERATOR_H
