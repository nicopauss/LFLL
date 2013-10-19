#ifndef LFLLCOMPLEMENTOPERATOR_H
#define LFLLCOMPLEMENTOPERATOR_H

#include "LFLLUnaryOperator.h"
#include "LFLLDefinitions.h"

LFLL_BEGIN_NAMESPACE

/**
  * Standard complement operator
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:[0,1] \rightarrow  f(x) = 1 - x
  * @f]
  */
struct LFLLComplementOperator
{
    inline dom operator()(dom val) const {
        return DOM_DIFF - val;
    }
};

LFLL_END_NAMESPACE


#endif //LFLLCOMPLEMENTOPERATOR_H
