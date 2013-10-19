#ifndef LFLLBOOLEAN_H
#define LFLLBOOLEAN_H

#include "LFLLTermBase.h"

LFLL_BEGIN_NAMESPACE


/**
  * Boolean term.
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     0, & x < 0.5 \\
     1, & x \geq 0.5 \\
   \end{array}
\right \}
  * @f]
  */
class LFLLBoolean : public LFLLTermBase
{
public:
    LFLLBoolean(bool val)
        : m_boolVal(val)
    {}

    inline dom membership(scalar val) const
    {
        return ((val >= HALF_SCALAR) == m_boolVal) ? MAX_DOM : MIN_DOM;
    }

private:
    bool m_boolVal;
};

LFLL_END_NAMESPACE

#endif //LFLLBOOLEAN_H
