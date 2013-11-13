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
#ifndef LFLLSIGMOIDPRODUCT_H
#define LFLLSIGMOIDPRODUCT_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>
#include <lfll/terms/LFLLSigmoid.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief Sigmoid product term
  *
  * Define the following membership function:
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R,  \rightarrow  f(x; slope1, infl1, slope2, infl2) = \frac{1}{1+e^{-slope1 (x - infl1)}} * \frac{1}{1+e^{-slope2 (x - infl2)}}
  * @f]
  *
  * It is similar to the Matlab function [psigmf](http://www.mathworks.com/help/fuzzy/psigmf.html).
  */
class LFLLSigmoidProduct
{
public:
    LFLLSigmoidProduct(
        scalar slope1, scalar infl1, 
        scalar slope2, scalar infl2)
        : m_sigmoid1(slope1, infl1)
        , m_sigmoid2(slope2, infl2)
    {}

    inline scalar membership(const scalar x) const
    {
        return m_sigmoid1.membership(x) * m_sigmoid2.membership(x);
    }

private:
    LFLLSigmoid m_sigmoid1;
    LFLLSigmoid m_sigmoid2;
};

LFLL_END_NAMESPACE

#endif //LFLLSIGMOIDPRODUCT_H
