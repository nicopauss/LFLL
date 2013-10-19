#ifndef LFLLZSHAPE_H
#define LFLLZSHAPE_H

#include "LFLLMath.h"
#include "LFLLTermBase.h"

LFLL_BEGIN_NAMESPACE

/**
  * S-Shape term
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     1, & x \leq minLim \\
     1 - 2 * (\frac{\displaystyle x - minLim}{\displaystyle maxLim-minLim})^2, & minLim < x < \frac{\displaystyle minLim+maxLim}{\displaystyle 2} \\
     2 * (\frac{\displaystyle x - maxLim}{\displaystyle maxLim-minLim})^2, & \frac{\displaystyle minLim+maxLim}{\displaystyle 2} \leq x < maxLim \\
     0, & x \geq maxLim \\
   \end{array}
\right \}
  * @f]
  *
  * http://www.mathworks.com/help/fuzzy/zmf.html
  */
class LFLLZShape : public LFLLBoundedTerm
{
public:
    LFLLZShape(scalar minLimit, scalar maxLimit)
        : LFLLBoundedTerm(minLimit, maxLimit)
        , m_invDifference(ONE_SCALAR / (maxLimit - minLimit))
        , m_halfRange((minLimit + maxLimit) / TWO_SCALAR)
    {}

    virtual inline dom membership(scalar val) const {
        if (val <= m_minLimit) {
            return MAX_DOM;
        } else if (val >= m_maxLimit) {
            return MIN_DOM;
        } else if (val <= m_halfRange) {
            val = (val - m_minLimit) * m_invDifference;
            return math::scalarToDom(ONE_SCALAR - TWO_SCALAR * val * val);
        } else {
            val = (val - m_maxLimit) * m_invDifference;
            return math::scalarToDom(TWO_SCALAR * val * val);
        }
    }

protected:
    scalar m_invDifference;
    scalar m_halfRange;
};

LFLL_END_NAMESPACE

#endif //LFLLZSHAPE_H
