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
#ifndef LFLLSUGENODEFUZZIFIERDETAIL_H
#define LFLLSUGENODEFUZZIFIERDETAIL_H


#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMath.h>
#include <lfll/engine/LFLLConsequence.h>
#include <lfll/engine/LFLLTuple.h>

LFLL_BEGIN_NAMESPACE

namespace detail {


template <LFLLSugenoDefuzzifyMethod D>
struct LFLLSugenoDefuzzifierMethodType;



template <size_t I, class TermTuple>
struct LFLLSugenoDefuzzifierImplIterator
{
    static void computeTermsValues(
        const TermTuple* terms,
        const scalar inputs[],
        scalar termsValues[])
    {
        LFLLSugenoDefuzzifierImplIterator<I-1, TermTuple>::
            computeTermsValues(terms, inputs, termsValues);
        termsValues[I-1] = 
            getLFLLTuple<I-1>(*terms)->computeTermValue(inputs);
    }
};

template <class TermTuple>
struct LFLLSugenoDefuzzifierImplIterator<0, TermTuple>
{
    static void computeTermsValues(
        const TermTuple*,
        const scalar[],
        scalar[])
    {}
};



template <class TermTuple, LFLLSugenoDefuzzifyMethod D>
class LFLLSugenoDefuzzifierImpl
{
public:
    LFLLSugenoDefuzzifierImpl(
        const TermTuple& terms)
        : m_terms(&terms)
    {}

    template <size_t NR>
    scalar defuzzifyConsequence(
        const scalar inputs[],
        const LFLLConsequence<NR>& consequence) const
    {
        typedef typename LFLLSugenoDefuzzifierMethodType<D>::type DefuzzifierMethod;

        scalar termsValues[TermTuple::tupleSize];
        LFLLSugenoDefuzzifierImplIterator<TermTuple::tupleSize, TermTuple>::
            computeTermsValues(m_terms, inputs, termsValues);

        return DefuzzifierMethod::
            defuzzifyConsequence(consequence, termsValues);
    }

private:
    const TermTuple* m_terms;
};


/******************************************************************
** Weighted Average
*******************************************************************/


struct LFLLSugenoDefuzzifierWeightedAverage
{
    template <size_t NR>
    static scalar defuzzifyConsequence(
        const LFLLConsequence<NR>& consequence,
        const scalar termsValues[])
    {
        scalar numerator = ZERO_SCALAR;
        scalar denominator = ZERO_SCALAR;

        // Iterate through each rules
        for (size_t i = 0 ; i < NR ; ++i)
        {
            const lfll_uint termIndex = consequence.getTermIndex(i);
            if (termIndex != 0) {
                const scalar ruleValue = consequence.getVal(i);
                numerator += ruleValue * termsValues[termIndex-1];
                denominator += ruleValue;
            }
        }

        if (lfll_math::isEqualTo(denominator, ZERO_SCALAR)) {
            return termsValues[0];
        }

        return numerator / denominator;
    }
};

template <>
struct LFLLSugenoDefuzzifierMethodType<LFLLSugenoWeightedAverage>
{
    typedef LFLLSugenoDefuzzifierWeightedAverage type;
};



/******************************************************************
** Weighted Sum
*******************************************************************/


struct LFLLSugenoDefuzzifierWeightedSum
{
    template <size_t NR>
    static scalar defuzzifyConsequence(
        const LFLLConsequence<NR>& consequence,
        const scalar termsValues[])
    {
        scalar numerator = ZERO_SCALAR;

        // Iterate through each rules
        for (size_t i = 0 ; i < NR ; ++i)
        {
            const lfll_uint termIndex = consequence.getTermIndex(i);
            if (termIndex != 0) {
                const scalar ruleValue = consequence.getVal(i);
                numerator += ruleValue * termsValues[termIndex-1];
            }
        }

        return numerator;
    }
};

template <>
struct LFLLSugenoDefuzzifierMethodType<LFLLSugenoWeightedSum>
{
    typedef LFLLSugenoDefuzzifierWeightedSum type;
};


}

LFLL_END_NAMESPACE


#endif //LFLLSUGENODEFUZZIFIERDETAIL_H
