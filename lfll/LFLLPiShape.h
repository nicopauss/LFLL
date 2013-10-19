#ifndef LFLLPISHAPE_H
#define LFLLPISHAPE_H

#include "LFLLSShape.h"
#include "LFLLZShape.h"
#include "LFLLMath.h"

LFLL_BEGIN_NAMESPACE

/**
  * Combination of S-Shape and Z-Shape
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     0, & x \leq sMinLim \\
     2 * (\frac{\displaystyle x - sMinLim}{\displaystyle sMaxLim-sMinLim})^2, & sMinLim < x < \frac{\displaystyle sMinLim+sMaxLim}{\displaystyle 2} \\
     1 - 2 * (\frac{\displaystyle x - sMaxLim}{\displaystyle sMaxLim-sMinLim})^2, & \frac{\displaystyle sMinLim+sMaxLim}{\displaystyle 2} \leq x < sMaxLim \\
     1, & sMaxLim \leq x \leq zMinLim \\
     1 - 2 * (\frac{\displaystyle x - zMinLim}{\displaystyle zMaxLim-zMinLim})^2, & zMinLim < x < \frac{\displaystyle zMinLim+zMaxLim}{\displaystyle 2} \\
     2 * (\frac{\displaystyle x - zMaxLim}{\displaystyle zMaxLim-zMinLim})^2, & \frac{\displaystyle zMinLim+zMaxLim}{\displaystyle 2} \leq x < zMaxLim \\
     0, & x \geq zMaxLim \\
   \end{array}
\right \}
  * @f]
  *
  * http://www.mathworks.com/help/fuzzy/pimf.html
  */
class LFLLPiShape : public LFLLTermBase
{
public:
    LFLLPiShape(scalar sMinLim, scalar sMaxLim,
        scalar zMinLim, scalar zMaxLim)
        : m_sShape(sMinLim, sMaxLim)
        , m_zShape(zMinLim, zMaxLim)
    {}

    virtual inline dom membership(scalar val) const
    {
        if (math::isGreaterThan(val, m_sShape.getMaxLimit())) {
            return m_zShape.membership(val);
        }
        return m_sShape.membership(val);
    }

private:
    LFLLSShape m_sShape;
    LFLLZShape m_zShape;
};

LFLL_END_NAMESPACE

#endif //LFLLPISHAPE_H
