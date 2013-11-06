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

LFLL_BEGIN_NAMESPACE

/**
  * \brief Z-Shape term
  *
  * Define the following membership function:
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x ; a, b) = \left \{
   \begin{array}{cc}
     1, & x \leq a \\
     1 - 2 * (\frac{\displaystyle x - a}{\displaystyle b-a})^2, & a < x < \frac{\displaystyle a+b}{\displaystyle 2} \\
     2 * (\frac{\displaystyle x - b}{\displaystyle b-a})^2, & \frac{\displaystyle a+b}{\displaystyle 2} \leq x < b \\
     0, & x \geq b \\
   \end{array}
\right \}
  * @f]
  *
  * It is similar to the Matlab function [zmf](http://www.mathworks.com/help/fuzzy/zmf.html).
  */
class LFLLZShape
{
public:
    LFLLZShape(scalar a, scalar b)
        : m_a(a)
        , m_b(b)
        , m_invDifference(ONE_SCALAR / (b - a))
        , m_halfRange((a + b) / TWO_SCALAR)
    {}

    inline scalar membership(const scalar x) const {
        if (x <= m_a) {
            return ONE_SCALAR;
        } else if (x >= m_b) {
            return ZERO_SCALAR;
        } else if (x <= m_halfRange) {
            const scalar midVal = (x - m_a) * m_invDifference;
            return ONE_SCALAR - TWO_SCALAR * midVal * midVal;
        } else {
            const scalar midVal = (x - m_b) * m_invDifference;
            return TWO_SCALAR * midVal * midVal;
        }
    }

private:
	scalar m_a;
	scalar m_b;
    scalar m_invDifference;
    scalar m_halfRange;
};

LFLL_END_NAMESPACE

#endif //LFLLZSHAPE_H
