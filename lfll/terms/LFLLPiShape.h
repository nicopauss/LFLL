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

LFLL_BEGIN_NAMESPACE

/**
  * \brief Combination of S-Shape and Z-Shape
  *
  * Define the following membership function:
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x ; a, b, c, d) = \left \{
   \begin{array}{cc}
     0, & x \leq a \\
     2 * (\frac{\displaystyle x - a}{\displaystyle b-a})^2, & a < x < \frac{\displaystyle a+b}{\displaystyle 2} \\
     1 - 2 * (\frac{\displaystyle x - b}{\displaystyle b-a})^2, & \frac{\displaystyle a+b}{\displaystyle 2} \leq x < b \\
     1, & b \leq x \leq c \\
     1 - 2 * (\frac{\displaystyle x - c}{\displaystyle d-c})^2, & c < x < \frac{\displaystyle c+d}{\displaystyle 2} \\
     2 * (\frac{\displaystyle x - d}{\displaystyle d-c})^2, & \frac{\displaystyle c+d}{\displaystyle 2} \leq x < d \\
     0, & x \geq d \\
   \end{array}
\right \}
  * @f]
  *
  * It is similar to the Matlab function [pimf](http://www.mathworks.com/help/fuzzy/pimf.html).
  */
class LFLLPiShape
{
public:
    LFLLPiShape(scalar a, scalar b, scalar c, scalar d)
        : m_a(a)
        , m_b(b)
        , m_c(c)
        , m_d(d)
        , m_invDifferenceS(ONE_SCALAR / (b - a))
        , m_halfRangeS((a + b) / TWO_SCALAR)
        , m_invDifferenceZ(ONE_SCALAR / (d - c))
        , m_halfRangeZ((c + d) / TWO_SCALAR)
    {}

    inline scalar membership(const scalar x) const
    {
    	if (x <= m_a) {
            return ZERO_SCALAR;
        } else if (x >= m_b) {
        	if (x <= m_c) {
				return ONE_SCALAR;
			} else if (x >= m_d) {
				return ZERO_SCALAR;
			} else if (x <= m_halfRangeZ) {
				const scalar midVal = (x - m_c) * m_invDifferenceZ;
				return ONE_SCALAR - TWO_SCALAR * midVal * midVal;
			} else {
				const scalar midVal = (x - m_d) * m_invDifferenceZ;
				return TWO_SCALAR * midVal * midVal;
			}
        } else if (x <= m_halfRangeS) {
            const scalar midVal = (x - m_a) * m_invDifferenceS;
            return TWO_SCALAR * midVal * midVal;
        } else {
            const scalar midVal = (x - m_b) * m_invDifferenceS;
            return ONE_SCALAR - TWO_SCALAR * midVal * midVal;
        }
    }

private:
	scalar m_a;
	scalar m_b;
	scalar m_c;
	scalar m_d;
    scalar m_invDifferenceS;
    scalar m_halfRangeS;
    scalar m_invDifferenceZ;
    scalar m_halfRangeZ;
};

LFLL_END_NAMESPACE

#endif //LFLLPISHAPE_H
