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


template <class TermTuple, size_t TermIndex>
struct LFLLSugenoDefuzzifierWeightedAverageIterator
{
	template <size_t NR, size_t NT>
    static void iterate(
        const TermTuple* terms,
        const scalar inputs[],
        const LFLLConsequence<NR, NT>& consequence,
        scalar& numerator,
        scalar& denominator)
    {
        LFLLSugenoDefuzzifierWeightedAverageIterator<TermTuple, TermIndex-1>::iterate(
            terms, inputs, consequence,
            numerator, denominator);
        const scalar termValue =
            getLFLLTuple<TermIndex-1>(*terms)->computeTermValue(inputs);
        for (size_t ruleIndex = 0 ; ruleIndex < NR ; ++ruleIndex)
        {
            const scalar ruleValue = consequence.getVal(
                TermIndex-1, ruleIndex);
            if (ruleValue != ZERO_SCALAR) {;
                numerator += ruleValue * termValue;
                denominator += ruleValue;
            }
        }
    }
};

template <class TermTuple>
struct LFLLSugenoDefuzzifierWeightedAverageIterator<TermTuple, 0>
{
	template <size_t NR, size_t NT>
    static void iterate(
        const TermTuple*,
        const scalar[],
        const LFLLConsequence<NR, NT>&,
        scalar&,
        scalar&)
    {}
};



/**
  * Sugeno defuzzifier with weighted average
  */
template <class TermTuple>
class LFLLSugenoDefuzzifierWeightedAverage
{
public:
    LFLLSugenoDefuzzifierWeightedAverage(
        const TermTuple& terms)
        : m_terms(&terms)
    {}

    template <size_t NR, size_t NT>
    scalar defuzzifyConsequence(
        const scalar inputs[],
        const LFLLConsequence<NR, NT>& consequence) const
    {
        scalar numerator = ZERO_SCALAR;
        scalar denominator = ZERO_SCALAR;

        LFLLSugenoDefuzzifierWeightedAverageIterator<TermTuple, NT>::iterate(
                    m_terms, inputs, consequence,
                    numerator, denominator);

        if (math::isEqualTo(denominator, ZERO_SCALAR)) {
            return getLFLLTuple<0>(*m_terms)->computeTermValue(inputs);
        }

        return numerator / denominator;
    }

private:
    const TermTuple* m_terms;
};





template <class TermTuple, size_t TermIndex>
struct LFLLSugenoDefuzzifierWeightedSumIterator
{
	template <size_t NR, size_t NT>
    static void iterate(
        const TermTuple* terms,
        const scalar inputs[],
        const LFLLConsequence<NR, NT>& consequence,
        scalar& numerator)
    {
        LFLLSugenoDefuzzifierWeightedSumIterator<TermTuple, TermIndex-1>::iterate(
            terms, inputs, consequence, numerator);
        const scalar termValue =
            getLFLLTuple<TermIndex-1>(*terms)->computeTermValue(inputs);
        for (size_t ruleIndex = 0 ; ruleIndex < NR ; ++ruleIndex)
        {
            const scalar ruleValue = consequence.getVal(
                TermIndex-1, ruleIndex);
            if (ruleValue != ZERO_SCALAR) {
                numerator += ruleValue * termValue;
            }
        }
    }
};

template <class TermTuple>
struct LFLLSugenoDefuzzifierWeightedSumIterator<TermTuple, 0>
{
	template <size_t NR, size_t NT>
    static void iterate(
        const TermTuple*,
        const scalar[],
        const LFLLConsequence<NR, NT>&,
        scalar&)
    {}
};



/**
  * Sugeno defuzzifier with weighted sum
  */
template <class TermTuple>
class LFLLSugenoDefuzzifierWeightedSum
{
public:
    LFLLSugenoDefuzzifierWeightedSum(
        const TermTuple& terms)
        : m_terms(&terms)
    {}

    template <size_t NR, size_t NT>
    scalar defuzzifyConsequence(
        const scalar inputs[],
        const LFLLConsequence<NR, NT>& consequence) const
    {
        scalar numerator = ZERO_SCALAR;

        LFLLSugenoDefuzzifierWeightedSumIterator<TermTuple, NT>::iterate(
			m_terms, inputs, consequence, numerator);

        return numerator;
    }

private:
    const TermTuple* m_terms;
};


/**
  * Get the right type of impl
  */

template <class TermTuple, LFLLSugenoDefuzzifyMethod D>
struct LFLLSugenoDefuzzifierType;

template <class TermTuple>
struct LFLLSugenoDefuzzifierType<TermTuple, LFLL_SUGENO_WEIGHTED_AVERAGE>
{
    typedef LFLLSugenoDefuzzifierWeightedAverage<TermTuple> type;
};

template <class TermTuple>
struct LFLLSugenoDefuzzifierType<TermTuple, LFLL_SUGENO_WEIGHTED_SUM>
{
    typedef LFLLSugenoDefuzzifierWeightedSum<TermTuple> type;
};

}

LFLL_END_NAMESPACE


#endif //LFLLSUGENODEFUZZIFIERDETAIL_H
