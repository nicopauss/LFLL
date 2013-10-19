#ifndef LFLLRRAMP_H
#define LFLLRRAMP_H

#include "LFLLMath.h"
#include "LFLLTermBase.h"


LFLL_BEGIN_NAMESPACE

/**
  * R Ramp term
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     1, & x \leq minLim \\
     \frac{\displaystyle x - minLim}{\displaystyle maxLim-minLim}, & minLim < x < maxLim \\
     0, & x \geq maxLim \\
   \end{array}
\right \}
  * @f]
  *
  @verbatim
           ------
          /
         /
        /
   -----
  @endverbatim
  */
class LFLLRRamp : public LFLLBoundedTerm
{
public:
    LFLLRRamp(scalar minLimit, scalar maxLimit)
        : LFLLBoundedTerm(minLimit, maxLimit)
        , m_invDifference(ONE_SCALAR / (maxLimit - minLimit))
    {}

    inline dom membership(scalar val) const
    {
        if (math::isLessOrEqualTo(val, m_minLimit)) {
            return MIN_DOM;
        } else if (math::isGreaterOrEqualTo(val, m_maxLimit)) {
            return MAX_DOM;
        }

        return math::scalarToDom((val - m_minLimit) * m_invDifference);
    }

private:
    scalar m_invDifference;
};

LFLL_END_NAMESPACE

#endif //LFLLRRAMP_H
