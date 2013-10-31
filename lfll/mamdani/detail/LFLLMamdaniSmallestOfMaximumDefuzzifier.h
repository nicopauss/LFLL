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
#ifndef LFLLMAMDANISMALLESTOFMAXIMUMDEFUZZIFIER_H
#define LFLLMAMDANISMALLESTOFMAXIMUMDEFUZZIFIER_H


#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>
#include <lfll/engine/LFLLConsequence.h>

#include <lfll/mamdani/detail/LFLLMamdaniDefuzzifierDetail.h>


LFLL_BEGIN_NAMESPACE

namespace detail {

template <class TermTuple, class ImpMethod, class AggMethod>
class LFLLMamdaniSmallestOfMaximumDefuzzifier
{
public:
    LFLLMamdaniSmallestOfMaximumDefuzzifier(
        const TermTuple& terms, 
        scalar minRange, scalar maxRange, 
        lfll_uint divisions,
        ImpMethod impMethod,
        AggMethod aggMethod)
        : m_termsValuesDefuzzifier(terms, impMethod, aggMethod)
        , m_minRange(minRange)
        , m_maxRange(maxRange)
        , m_divisions(divisions)
        , m_dx((maxRange - minRange) / divisions)
    {}


    template <size_t NR>
    scalar defuzzifyConsequence(
        const LFLLConsequence<NR>& consequence) const
    {
        scalar x = m_minRange + HALF_SCALAR * m_dx;
        scalar yMax = ZERO_SCALAR;
        scalar xLeft = m_minRange;
        
        for (lfll_uint i = 0 ; i < m_divisions ; ++i, x += m_dx) {
            const scalar y = 
                m_termsValuesDefuzzifier.computeTermValue(
                    x, consequence);
            if (lfll_math::isGreaterThan(y, yMax)) {
                yMax = y;
                xLeft = x;
            }
        }
        return xLeft;
    }


private:
    const LFLLMamdaniDefuzzifierTermsValues<TermTuple, ImpMethod, AggMethod>
        m_termsValuesDefuzzifier;
    const scalar m_minRange;
    const scalar m_maxRange;
    const lfll_uint m_divisions;
    const scalar m_dx;

};



template <class TermTuple, class ImpMethod, class AggMethod>
struct LFLLMamdaniDefuzzifierMethodType
    <LFLLMamdaniSmallestOfMaximum, TermTuple, ImpMethod, AggMethod>
{
    typedef LFLLMamdaniSmallestOfMaximumDefuzzifier
        <TermTuple, ImpMethod, AggMethod> type;
};



}

LFLL_END_NAMESPACE


#endif //LFLLMAMDANISMALLESTOFMAXIMUMDEFUZZIFIER_H
