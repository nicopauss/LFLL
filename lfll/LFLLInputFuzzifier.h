#ifndef LFLLINPUTVARIABLE_H
#define LFLLINPUTVARIABLE_H

#include "LFLLDefinitions.h"

#include "LFLLMembership.h"
#include "LFLLTermBase.h"

LFLL_BEGIN_NAMESPACE

/**
* Represent an input variable.
*
* NT define the number of terms.
*/
template <size_t NT>
class LFLLInputFuzzifier {
public:
    typedef LFLLMembership<NT> InputMembershipDegrees;
    static const size_t nbTerms = NT;

public:
    /**
     * @brief Constructor
     * @param terms Terms of the input variable.
     * @warning The variable terms must have the same or greater lifespan than
     *  this object.
     */
    LFLLInputFuzzifier(const LFLLTerms<NT>& terms);

    /**
     * @brief fuzzifyVariable
     * @param input The input variable
     * @return
     */
    LFLLMembership<NT> fuzzifyVariable(scalar input) const;
private:
    const LFLLTerms<NT>* m_terms;
};

/************************************************************************/
/* Template methods                                                     */
/************************************************************************/


template <size_t NT>
inline LFLLInputFuzzifier<NT>::LFLLInputFuzzifier(const LFLLTerms<NT>& terms)
    : m_terms(&terms)
{}


template <size_t NT>
inline LFLLMembership<NT> LFLLInputFuzzifier<NT>::fuzzifyVariable(
    scalar input) const
{
    LFLLMembership<NT> result;
    for (size_t i = 0 ; i < NT ; ++i) {
        result.setVal(i, m_terms->terms[i]->membership(input));
    }
    return result;
}

LFLL_END_NAMESPACE

#endif //LFLLINPUTVARIABLE_H
