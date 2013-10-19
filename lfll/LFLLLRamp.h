#ifndef LFLLLRAMP_H
#define LFLLLRAMP_H

#include "LFLLMath.h"
#include "LFLLTermBase.h"

LFLL_BEGIN_NAMESPACE

/**
  * L Ramp term
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     1, & x \leq minLim \\
     \frac{\displaystyle maxLim - x}{\displaystyle maxLim-minLim}, & minLim < x < maxLim \\
     0, & x \geq maxLim \\
   \end{array}
\right \}
  * @f]
  */
class LFLLLRamp : public LFLLBoundedTerm
{
public:
    LFLLLRamp(scalar minLimit, scalar maxLimit)
        : LFLLBoundedTerm(minLimit, maxLimit)
        , m_invDifference(ONE_SCALAR / (maxLimit - minLimit))
    {}

    inline dom membership(scalar val) const
    {
        if (math::isLessOrEqualTo(val, m_minLimit)) {
            return MAX_DOM;
        } else if (math::isGreaterOrEqualTo(val, m_maxLimit)) {
            return MIN_DOM;
        }

        return math::scalarToDom((m_maxLimit - val) * m_invDifference);
    }

protected:
    scalar m_invDifference;
};

LFLL_END_NAMESPACE


#endif //LFLLLRAMP_H
