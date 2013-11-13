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
#ifndef LFLLMAMDANIDEFUZZIFIERDETAIL_H
#define LFLLMAMDANIDEFUZZIFIERDETAIL_H


#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLConsequence.h>
#include <lfll/engine/LFLLArray.h>
#include <lfll/engine/LFLLTuple.h>

LFLL_BEGIN_NAMESPACE

namespace detail {


template <LFLLMamdaniDefuzzifyMethod D, class TermTuple, 
    class ImpMethod, class AggMethod>
struct LFLLMamdaniDefuzzifierMethodType;



template <size_t I, class TermTuple>
struct LFLLMamdaniDefuzzifierTermsValuesIterator
{
    static void computeTermsValues(
        const TermTuple* terms,
        const scalar x,
        LFLLArray<TermTuple::tupleSize>& termsValues)
    {
        LFLLMamdaniDefuzzifierTermsValuesIterator<I-1, TermTuple>::
            computeTermsValues(terms, x, termsValues);
        termsValues[I-1] = 
            getLFLLTuple<I-1>(*terms)->membership(x);
    }
};

template <class TermTuple>
struct LFLLMamdaniDefuzzifierTermsValuesIterator<0, TermTuple>
{
    static void computeTermsValues(
        const TermTuple*,
        const scalar,
        LFLLArray<TermTuple::tupleSize>&)
    {}
};



template <class TermTuple, class ImpMethod, class AggMethod>
class LFLLMamdaniDefuzzifierTermsValues
{
public:
    LFLLMamdaniDefuzzifierTermsValues(
        const TermTuple& terms,
        ImpMethod impMethod,
        AggMethod aggMethod)
        : m_terms(&terms)
        , m_impMethod(impMethod)
        , m_aggMethod(aggMethod)
    {}

    template <size_t NR>
    scalar computeTermValue(
        scalar x,
        const LFLLConsequence<NR>& consequence) const
    {
        LFLLArray<TermTuple::tupleSize> termsValues;

        LFLLMamdaniDefuzzifierTermsValuesIterator
            <TermTuple::tupleSize, TermTuple>::
            computeTermsValues(m_terms, x, termsValues);

        scalar result = ZERO_SCALAR;

        // Iterate through each rules
        for (size_t i = 0 ; i < NR ; ++i) {
            const lfll_uint termIndex = consequence.getTermIndex(i);

            if (termIndex != 0) {
                const scalar ruleValue = consequence.getVal(i);
                const scalar termValue = termsValues[termIndex-1];
                result = m_aggMethod(result, m_impMethod(ruleValue, termValue));
            }
        }

        return result;
    }

private:
    const TermTuple* m_terms;
    const ImpMethod m_impMethod;
    const AggMethod m_aggMethod;
};


}

LFLL_END_NAMESPACE


#endif //LFLLMAMDANIDEFUZZIFIERDETAIL_H
