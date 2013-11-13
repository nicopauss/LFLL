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

#include <lfll/engine/LFLLDefinitions.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief Trapezoidal term
  *
  * Define the following membership function:
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x ; a, b, c, d) = \left \{
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
  * It is similar to the Matlab function [trapmf](http://www.mathworks.com/help/fuzzy/trapmf.html).
  */
class LFLLTrapezoid
{
public:
    LFLLTrapezoid(scalar a, scalar b, scalar c, scalar d)
        : m_a(a)
        , m_b(b)
        , m_c(c)
        , m_d(d)
        , m_invDifferenceAB(ONE_SCALAR / (b - a))
        , m_invDifferenceCD(ONE_SCALAR / (d - c))
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
    		}
    		return (m_d - x) * m_invDifferenceCD;
    	}
    	return (x - m_a) * m_invDifferenceAB;
    }
private:
	scalar m_a;
	scalar m_b;
	scalar m_c;
	scalar m_d;
    scalar m_invDifferenceAB;
    scalar m_invDifferenceCD;
};

LFLL_END_NAMESPACE


#endif //LFLLTRAPEZOID_H
