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
#ifndef LFLLAGGREGATOR_H
#define LFLLAGGREGATOR_H

#include <cassert>

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMembership.h>
#include <lfll/engine/LFLLConsequence.h>
#include <lfll/norms/LFLLSNorm.h>

LFLL_BEGIN_NAMESPACE

/**
 * Aggregate consequences to membership using a s-norm operator.
 * Default is max operator.
 * It is useful if you want to chain up systems.
 */
template<typename SNorm = LFLLMax>
class LFLLAggregator
{
public:
    LFLLAggregator()
        : m_sNorm()
    {}

    template <size_t NR, size_t NT>
    LFLLMembership<NT> aggregateConsequence(
        const LFLLConsequence<NR, NT>& consequence) const;
private:
    const SNorm m_sNorm;
};


template<typename BinaryOperatorType>
template <size_t NR, size_t NT>
LFLLMembership<NT> LFLLAggregator<BinaryOperatorType>::aggregateConsequence(
    const LFLLConsequence<NR, NT>& consequence) const
{
    LFLLMembership<NT> retValue;
    for (size_t termIndex = 0 ; termIndex < NT ; ++termIndex) {
        scalar termValue;
        bool hasPrevTerm = false;
        for (size_t ruleIndex = 0 ; ruleIndex < NR ; ++ruleIndex) {
            const scalar consequenceValue =
                    consequence.getVal(termIndex, ruleIndex);
            if (hasPrevTerm) {
                termValue = m_sNorm(termValue, consequenceValue);
            } else {
                termValue = consequenceValue;
                hasPrevTerm = true;
            }
        }
        retValue.setVal(termIndex, termValue);
    }
    return retValue;
}

LFLL_END_NAMESPACE

#endif //LFLLAGGREGATOR_H
