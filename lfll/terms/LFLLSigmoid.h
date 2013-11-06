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
#ifndef LFLLSIGMOID_H
#define LFLLSIGMOID_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief Sigmoid term
  *
  * Define the following membership function:
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R,  \rightarrow  f(x; slope, infl) = \frac{1}{1+e^{-slope (x - infl)}}
  * @f]
  *
  * It is similar to the Matlab function [sigmf](http://www.mathworks.com/help/fuzzy/sigmf.html).
  */
class LFLLSigmoid
{
public:
    LFLLSigmoid(scalar slope, scalar infl)
        : m_negSlope(-slope)
        , m_infl(infl)
    {}

    inline scalar membership(const scalar x) const
    {
        return ONE_SCALAR / (ONE_SCALAR + lfll_math::exp(m_negSlope * (x - m_infl)));
    }

protected:
    scalar m_negSlope;
    scalar m_infl;
};

LFLL_END_NAMESPACE

#endif //LFLLSIGMOID_H
