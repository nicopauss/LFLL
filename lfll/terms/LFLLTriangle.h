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
#ifndef LFLLTRIANGLE_H
#define LFLLTRIANGLE_H

#include <lfll/engine/LFLLDefinitions.h>

LFLL_BEGIN_NAMESPACE


/**
  * \brief Triangle term
  *
  * Define the following membership function:
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
  @verbatim
         .
        / \
       /   \
      /     \
   ---       ---
  @endverbatim
  *
  * It is similar to the Matlab function [trimf](http://www.mathworks.com/help/fuzzy/trimf.html).
  */
class LFLLTriangle
{
public:
    LFLLTriangle(scalar a, scalar b, scalar c)
        : m_a(a)
        , m_b(b)
        , m_c(c)
        , m_invDiffAB(ONE_SCALAR / (b - a))
        , m_invDiffBC(ONE_SCALAR / (c - b))
    {}

    inline scalar membership(const scalar x) const
    {
        if ((x <= m_a) ||
            (x >= m_c)) {
            return ZERO_SCALAR;
        } else if (x == m_b) {
            return ONE_SCALAR;
        } else if (x < m_b) {
            return (x - m_a) * m_invDiffAB;
        } else {
            return (m_c - x) * m_invDiffBC;
        }
    }

private:
    scalar m_a;
    scalar m_b;
    scalar m_c;
    scalar m_invDiffAB;
    scalar m_invDiffBC;
};

LFLL_END_NAMESPACE


#endif //LFLLTRIANGLE_H
