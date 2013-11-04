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
#ifndef LFLLGAUSSIANPRODUCT_H
#define LFLLGAUSSIANPRODUCT_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>

LFLL_BEGIN_NAMESPACE

/**
  * Gaussian product term
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x, \sigma1, \mu1, \sigma2, \mu2) = \left \{
   \begin{array}{cc}
     e^(\frac{-(x - \mu1)^2}{2 \sigma1^2}), & x < \mu1 \\
     1, & \mu1 \leq x \leq \mu2 \\
     e^(\frac{-(x - \mu2)^2}{2 \sigma2^2}), & x > \mu2 \\
   \end{array}
\right \}
  * @f]
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R,  \rightarrow   = 
  * @f]
  *
  * http://www.mathworks.com/help/fuzzy/gauss2mf.html
  */
class LFLLGaussianProduct
{
public:
    LFLLGaussianProduct(scalar sigma1, scalar mean1, scalar sigma2, scalar mean2)
        : m_negInvTwiceSigma1Square(-ONE_SCALAR / (TWO_SCALAR * sigma1 * sigma1))
        , m_mean1(mean1)
        , m_negInvTwiceSigma2Square(-ONE_SCALAR / (TWO_SCALAR * sigma2 * sigma2))
        , m_mean2(mean2)
    {}

    inline scalar membership(const scalar val) const
    {
        if (val < m_mean1) {
            const scalar diffValMean1 = val - m_mean1;
            return lfll_math::exp(diffValMean1 * diffValMean1 * m_negInvTwiceSigma1Square);
        } else if (val > m_mean2) {
            const scalar diffValMean2 = val - m_mean2;
            return lfll_math::exp(diffValMean2 * diffValMean2 * m_negInvTwiceSigma2Square);
        } else {
            return ONE_SCALAR;
        }
    }

protected:
    scalar m_negInvTwiceSigma1Square;
    scalar m_mean1;
    scalar m_negInvTwiceSigma2Square;
    scalar m_mean2;
};

LFLL_END_NAMESPACE

#endif //LFLLGAUSSIANPRODUCT_H
