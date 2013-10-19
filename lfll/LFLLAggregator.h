#ifndef LFLLAGGREGATOR_H
#define LFLLAGGREGATOR_H

#include <cassert>

#include "LFLLDefinitions.h"
#include "LFLLBinaryOperator.h"
#include "LFLLMembership.h"
#include "LFLLConsequence.h"
#include "LFLLMaxOperator.h"

LFLL_BEGIN_NAMESPACE

/**
 * Aggregate consequences to membership using a binary operator.
 * Defualt is the max operator.
 * It is useful if you want to chain up systems.
 */
template<typename BinaryOperatorType = LFLLMaxOperator>
class LFLLAggregator
{
public:
    LFLLAggregator()
        : m_binaryOperator()
    {}

    template <size_t NR, size_t NT>
    LFLLMembership<NT> aggregateConsequence(
        const LFLLConsequence<NR, NT>& consequence) const;
private:
    const BinaryOperatorType m_binaryOperator;
};


template<typename BinaryOperatorType>
template <size_t NR, size_t NT>
LFLLMembership<NT> LFLLAggregator<BinaryOperatorType>::aggregateConsequence(
    const LFLLConsequence<NR, NT>& consequence) const
{
    LFLLMembership<NT> retValue;
    for (size_t termIndex = 0 ; termIndex < NT ; ++termIndex) {
        dom termValue;
        bool hasPrevTerm = false;
        for (size_t ruleIndex = 0 ; ruleIndex < NR ; ++ruleIndex) {
            const dom consequenceValue =
                    consequence.membershipValue(termIndex, ruleIndex);
            if (hasPrevTerm) {
                termValue = m_binaryOperator(termValue, consequenceValue);
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
