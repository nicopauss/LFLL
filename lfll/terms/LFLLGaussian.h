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
#ifndef LFLLGAUSSIAN_H
#define LFLLGAUSSIAN_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief Gaussian term
  *
  * Define the following membership function:
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R,  \rightarrow  f(x, \sigma, \mu) = e^(\frac{-(x - \mu)^2}{2 \sigma^2})
  * @f]
  *
  * It is similar to the Matlab function [gaussmf](http://www.mathworks.com/help/fuzzy/gaussmf.html).
  */
class LFLLGaussian
{
public:
    LFLLGaussian(scalar sigma, scalar mean)
        : m_negInvTwiceSigmaSquare(-ONE_SCALAR / (TWO_SCALAR * sigma * sigma))
        , m_mean(mean)
    {}

    inline scalar membership(const scalar x) const
    {
        const scalar diffValMean = x - m_mean;
        return lfll_math::exp(diffValMean * diffValMean * m_negInvTwiceSigmaSquare);
    }

private:
    scalar m_negInvTwiceSigmaSquare;
    scalar m_mean;
};

LFLL_END_NAMESPACE

#endif //LFLLGAUSSIAN_H
