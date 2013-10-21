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
#ifndef LFLLSUGENODEFUZZIFIER_H
#define LFLLSUGENODEFUZZIFIER_H

#include <cassert>

#include <lfll/LFLLMath.h>
#include <lfll/LFLLConsequence.h>


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
