#ifndef LFLLRECTANGLE_H
#define LFLLRECTANGLE_H

#include "LFLLTermBase.h"
#include "LFLLMath.h"

LFLL_BEGIN_NAMESPACE

/**
  * Rectangle term
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     0, & x \leq minLim \\
     1, & minLim < x < maxLim \\
     0, & x \geq maxLim \\
   \end{array}
\right \}
  * @f]
  */
class LFLLRectangle : public LFLLBoundedTerm
{
public:
    LFLLRectangle(scalar minLimit, scalar maxLimit)
        : LFLLBoundedTerm(minLimit, maxLimit)
    {}


    virtual inline dom membership(scalar val) const {
        if (math::isGreaterOrEqualTo(val, m_minLimit) &&
            math::isLessOrEqualTo(val, m_maxLimit)) {
                return MAX_DOM;
        }
        return MIN_DOM;
    }
};

LFLL_END_NAMESPACE

#endif //LFLLRECTANGLE_H
