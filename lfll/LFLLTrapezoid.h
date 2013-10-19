#ifndef LFLLTRAPEZOID_H
#define LFLLTRAPEZOID_H
#include <cassert>

#include "LFLLMath.h"
#include "LFLLLRamp.h"
#include "LFLLRRamp.h"

LFLL_BEGIN_NAMESPACE

/**
  * Trapezoidal term
  *
  * Combinaison of R-Ramp and L-Ramp
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     0, & x \leq a \\
     \frac{\displaystyle x - a}{\displaystyle b - a}, & a < x < b \\
     1, & b \leq x \leq c \\
     \frac{\displaystyle d - x}{\displaystyle d - c}, & c < x < d \\
     0, & x \geq d \\
   \end{array}
\right \}
  * @f]
  *
  * http://www.mathworks.com/help/fuzzy/trapmf.html
  */
class LFLLTrapezoid : public LFLLTermBase
{
public:
    LFLLTrapezoid(scalar a, scalar b, scalar c, scalar d)
        : m_rRamp(a, b)
        , m_lRamp(c, d)
    {}

    virtual dom membership(scalar val) const
    {
        if (math::isGreaterThan(val, m_rRamp.getMaxLimit())) {
            return m_lRamp.membership(val);
        }
        return m_rRamp.membership(val);
    }
private:
    LFLLRRamp m_rRamp;
    LFLLLRamp m_lRamp;
};

LFLL_END_NAMESPACE


#endif //LFLLTRAPEZOID_H
