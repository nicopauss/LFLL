/*
The MIT License (MIT)

Copyright (c) 2013 Nicolas Pauss

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef LFLLTRAPEZOID_H
#define LFLLTRAPEZOID_H

#include <cassert>

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>
#include <lfll/terms/LFLLLRamp.h>
#include <lfll/terms/LFLLRRamp.h>

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
  @verbatim
         ---
        /   \
       /     \
      /       \
   ---         ---
  @endverbatim
  *
  * http://www.mathworks.com/help/fuzzy/trapmf.html
  */
class LFLLTrapezoid
{
public:
    LFLLTrapezoid(scalar a, scalar b, scalar c, scalar d)
        : m_rRamp(a, b)
        , m_lRamp(c, d)
    {}

    inline scalar membership(const scalar val) const
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
