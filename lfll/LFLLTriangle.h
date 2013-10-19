#ifndef LFLLTRIANGLE_H
#define LFLLTRIANGLE_H

#include "LFLLTrapezoid.h"

LFLL_BEGIN_NAMESPACE


/**
  * Traingle term
  *
  * Special case of trapezoidal term where b = c
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     0, & x \leq a \\
     \frac{\displaystyle x - a}{\displaystyle b - a}, & a < x < b \\
     \frac{\displaystyle c - x}{\displaystyle c - b}, & b \leq x < c \\
     0, & x \geq c \\
   \end{array}
\right \}
  * @f]
  *
  * http://www.mathworks.com/help/fuzzy/trimf.html
  */
class LFLLTriangle : public LFLLTrapezoid
{
public:
    LFLLTriangle(scalar a, scalar b, scalar c)
        : LFLLTrapezoid(a, b, b, c)
    {}
};

LFLL_END_NAMESPACE


#endif //LFLLTRIANGLE_H
