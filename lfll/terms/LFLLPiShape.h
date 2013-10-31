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
#ifndef LFLLPISHAPE_H
#define LFLLPISHAPE_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>
#include <lfll/terms/LFLLSShape.h>
#include <lfll/terms/LFLLZShape.h>

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
class LFLLPiShape
{
public:
    LFLLPiShape(scalar sMinLim, scalar sMaxLim,
        scalar zMinLim, scalar zMaxLim)
        : m_sShape(sMinLim, sMaxLim)
        , m_zShape(zMinLim, zMaxLim)
    {}

    inline scalar membership(const scalar val) const
    {
        if (lfll_math::isGreaterThan(val, m_sShape.getMaxLimit())) {
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
