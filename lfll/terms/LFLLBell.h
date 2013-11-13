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
#ifndef LFLLBELL_H
#define LFLLBELL_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief Bell term
  *
  * Define the following membership function:
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R,  \rightarrow  f(x; a, b, c) = \frac{1}{1+|\frac{x-c}{a}|^{2b}}
  * @f]
  *
  * It is similar to the Matlab function [gbellmf](http://www.mathworks.com/help/fuzzy/gbellmf.html).
  */
class LFLLBell
{
public:

    LFLLBell(scalar a, scalar b, scalar c)
        : m_invA(ONE_SCALAR / a)
        , m_twiceB(TWO_SCALAR * b)
        , m_c(c)
    {}

    inline scalar membership(const scalar x) const
    {
        return ONE_SCALAR / (ONE_SCALAR + 
          lfll_math::pow(lfll_math::abs((x - m_c) * m_invA), m_twiceB));
    }

private:
    scalar m_invA;
    scalar m_twiceB;
    scalar m_c;
};

LFLL_END_NAMESPACE

#endif //LFLLBELL_H
