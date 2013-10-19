#ifndef LFLLSUGENODEFUZZIFIER_H
#define LFLLSUGENODEFUZZIFIER_H

#include <cassert>

#include "LFLLMath.h"
#include "LFLLConsequence.h"


LFLL_BEGIN_NAMESPACE

template <size_t NT>
struct LFLLSugenoCrispValues
{
    scalar values[NT];
};


/**
  * Sugeno defuzzifier with crisp values
  */
template <size_t NR, size_t NT>
class LFLLSugenoDefuzzifier
{
public:
    static const size_t nbTerms = NT;
    static const size_t nbRules = NR;

public:
    LFLLSugenoDefuzzifier(const LFLLSugenoCrispValues<NT>& crispValues);

    scalar defuzzifyConsequence(
        const LFLLConsequence<NR, NT>& consequence) const;

private:
    const LFLLSugenoCrispValues<NT> m_crispValues;
};

/************************************************************************/
/* Template methods */
/************************************************************************/

template <size_t NR, size_t NT>
inline LFLLSugenoDefuzzifier<NR, NT>::
    LFLLSugenoDefuzzifier(const LFLLSugenoCrispValues<NT>& crispValues)
    : m_crispValues(crispValues)
{
}

template <size_t NR, size_t NT>
inline scalar LFLLSugenoDefuzzifier<NR, NT>::defuzzifyConsequence(
    const LFLLConsequence<NR, NT>& consequence) const
{
    scalar numerator = ZERO_SCALAR;
    scalar denominator = ZERO_SCALAR;

    for (size_t termIndex = 0 ; termIndex < NT ; ++termIndex) {
        const scalar termValue = m_crispValues.values[termIndex];
        for (size_t ruleIndex = 0 ; ruleIndex < NR ; ++ruleIndex)
        {
            const dom ruleValue = consequence.membershipValue(termIndex,
                ruleIndex);
            if (ruleValue != MIN_DOM) {
                const scalar ruleValueScalar = math::domToScalar(ruleValue);
                numerator += ruleValueScalar * termValue;
                denominator += ruleValueScalar;
            }
        }
    }

    if (math::isEqualTo(denominator, ZERO_SCALAR)) {
        return m_crispValues.values[0];
    }

    return numerator / denominator;
}

LFLL_END_NAMESPACE


#endif //LFLLSUGENODEFUZZIFIER_H
