#ifndef LFLLMAXOPERATOR_H
#define LFLLMAXOPERATOR_H

#include "LFLLBinaryOperator.h"

LFLL_BEGIN_NAMESPACE

/**
  * Standard Max operator
  */
struct LFLLMaxOperator : public LFLLBinaryOperator
{
    inline dom operator()(dom val1, dom val2) const {
        return (val1 < val2) ? val2 : val1;
    }
};

LFLL_END_NAMESPACE


#endif //LFLLMAXOPERATOR_H
