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
#ifndef LFLLZSHAPE_H
#define LFLLZSHAPE_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>
#include <lfll/terms/LFLLBoundedTerm.h>

LFLL_BEGIN_NAMESPACE

/**
  * Z-Shape term
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

    inline scalar membership(const scalar val) const {
        if (val <= m_minLimit) {
            return ONE_SCALAR;
        } else if (val >= m_maxLimit) {
            return ZERO_SCALAR;
        } else if (val <= m_halfRange) {
            const scalar midVal = (val - m_minLimit) * m_invDifference;
            return ONE_SCALAR - TWO_SCALAR * midVal * midVal;
        } else {
            const scalar midVal = (val - m_maxLimit) * m_invDifference;
            return TWO_SCALAR * midVal * midVal;
        }
    }

protected:
    scalar m_invDifference;
    scalar m_halfRange;
};

LFLL_END_NAMESPACE

#endif //LFLLZSHAPE_H
