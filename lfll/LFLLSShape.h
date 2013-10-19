#ifndef LFLLSSHAPE_H
#define LFLLSSHAPE_H

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
     0, & x \leq minLim \\
     2 * (\frac{\displaystyle x - minLim}{\displaystyle maxLim-minLim})^2, & minLim < x < \frac{\displaystyle minLim+maxLim}{\displaystyle 2} \\
     1 - 2 * (\frac{\displaystyle x - maxLim}{\displaystyle maxLim-minLim})^2, & \frac{\displaystyle minLim+maxLim}{\displaystyle 2} \leq x < maxLim \\
     1, & x \geq maxLim \\
   \end{array}
\right \}
  * @f]
  *
  * http://www.mathworks.com/help/fuzzy/smf.html
  */
class LFLLSShape : public LFLLBoundedTerm
{
public:
    LFLLSShape(scalar minLimit, scalar maxLimit)
        : LFLLBoundedTerm(minLimit, maxLimit)
        , m_invDifference(ONE_SCALAR / (maxLimit - minLimit))
        , m_halfRange((minLimit + maxLimit) / TWO_SCALAR)
    {}

    virtual inline dom membership(scalar val) const
    {
        if (val <= m_minLimit) {
            return MIN_DOM;
        } else if (val >= m_maxLimit) {
            return MAX_DOM;
        } else if (val <= m_halfRange) {
            val = (val - m_minLimit) * m_invDifference;
            return math::scalarToDom(TWO_SCALAR * val * val);
        } else {
            val = (val - m_maxLimit) * m_invDifference;
            return math::scalarToDom(ONE_SCALAR - TWO_SCALAR * val * val);
        }
    }

protected:
    scalar m_invDifference;
    scalar m_halfRange;
};

LFLL_END_NAMESPACE

#endif //LFLLSSHAPE_H
