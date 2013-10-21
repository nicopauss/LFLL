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
#ifndef LFLLINPUTVARIABLE_H
#define LFLLINPUTVARIABLE_H

#include <lfll/LFLLDefinitions.h>

#include <lfll/LFLLMembership.h>
#include <lfll/LFLLTermBase.h>

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
