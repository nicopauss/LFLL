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
#ifndef LFLLRECTANGLE_H
#define LFLLRECTANGLE_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief Rectangle term
  *
  * Define the following membership function:
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x ; a, b) = \left \{
   \begin{array}{cc}
     0, & x \leq a \\
     1, & a < x < c \\
     0, & x \geq b \\
   \end{array}
\right \}
  * @f]
  */
class LFLLRectangle
{
public:
    LFLLRectangle(scalar a, scalar b)
        : m_a(a)
        , m_b(b)
    {}


    inline scalar membership(const scalar x) const {
        if (lfll_math::isGreaterOrEqualTo(x, m_a) &&
            lfll_math::isLessOrEqualTo(x, m_b))
        {
                return ONE_SCALAR;
        }
        return ZERO_SCALAR;
    }
    
private:
	scalar m_a;
	scalar m_b;
};

LFLL_END_NAMESPACE

#endif //LFLLRECTANGLE_H
