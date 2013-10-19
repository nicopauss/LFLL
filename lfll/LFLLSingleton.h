#ifndef LFLLSINGLETON_H
#define LFLLSINGLETON_H

#include "LFLLTermBase.h"
#include "LFLLMath.h"

LFLL_BEGIN_NAMESPACE

/**
  * Singleton Term
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     1, & x = val \\
     0, & x \neq val \\
   \end{array}
\right \}
  * @f]
  */
class LFLLSingleton : public LFLLTermBase
{
public:

    LFLLSingleton(scalar val)
        : m_val(val)
    {}

    virtual inline dom membership(scalar val) const
    {
        if (math::isEqualTo(val, m_val)) {
            return MAX_DOM;
        }
        return MIN_DOM;
    }
protected:
    scalar m_val;
};

LFLL_END_NAMESPACE


#endif //LFLLSINGLETON_H
