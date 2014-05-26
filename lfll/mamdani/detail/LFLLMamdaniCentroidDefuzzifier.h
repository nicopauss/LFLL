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
#ifndef LFLLMAMDANICENTROIDDEFUZZIFIER_H
#define LFLLMAMDANICENTROIDDEFUZZIFIER_H


#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>
#include <lfll/engine/LFLLConsequence.h>

#include <lfll/mamdani/detail/LFLLMamdaniDefuzzifierDetail.h>


LFLL_BEGIN_NAMESPACE

namespace detail {

template <class TermTuple, class ImpMethod, class AggMethod>
class LFLLMamdaniCentroidDefuzzifier
{
public:
    LFLLMamdaniCentroidDefuzzifier(
        const TermTuple& terms, 
        scalar minRange, scalar maxRange, 
        lfll_uint divisions,
        ImpMethod impMethod,
        AggMethod aggMethod)
        : m_termsValuesDefuzzifier(terms, impMethod, aggMethod)
        , m_divisions(divisions)
        , m_dx((maxRange - minRange) / divisions)
        , m_xBegin(minRange + HALF_SCALAR * m_dx)
    {}


    template <size_t NR>
    scalar defuzzifyConsequence(
        const LFLLConsequence<NR>& consequence) const
    {
        scalar x = m_xBegin;
        scalar xcentroid = ZERO_SCALAR;
        scalar area = ZERO_SCALAR;
        for (lfll_uint i = m_divisions ; i > 0 ; --i, x += m_dx) {
            const scalar y = 
                m_termsValuesDefuzzifier.computeTermValue(
                    x, consequence);
            xcentroid += x * y;
            area += y;
        }
        return xcentroid / area;
    }


private:
    const LFLLMamdaniDefuzzifierTermsValues<TermTuple, ImpMethod, AggMethod>
        m_termsValuesDefuzzifier;
    const lfll_uint m_divisions;
    const scalar m_dx;
    const scalar m_xBegin;

};



template <class TermTuple, class ImpMethod, class AggMethod>
struct LFLLMamdaniDefuzzifierMethodType
    <LFLLMamdaniCentroid, TermTuple, ImpMethod, AggMethod>
{
    typedef LFLLMamdaniCentroidDefuzzifier
        <TermTuple, ImpMethod, AggMethod> type;
};



}

LFLL_END_NAMESPACE


#endif //LFLLMAMDANICENTROIDDEFUZZIFIER_H
