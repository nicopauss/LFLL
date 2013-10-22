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

#include <lfll/LFLLStaticAssert.h>
#include <lfll/LFLLMembership.h>

LFLL_BEGIN_NAMESPACE

/**
* Represent an input variable.
*/
template <class InputTermsType>
class LFLLInputFuzzifier {
public:
    /**
     * @brief Constructor
     * @param terms Terms of the input variable.
     * @warning The variable terms must have the same or greater lifespan than
     *  this object.
     */
    LFLLInputFuzzifier(const InputTermsType& terms);

    /**
     * @brief fuzzifyVariable
     * @param input The input variable
     * @return
     */
    LFLLMembership<InputTermsType::tupleSize>
            fuzzifyVariable(scalar input) const;

private:
    template <size_t I>
    struct Iterator
    {
        static void iterate(
            const InputTermsType* terms,
            scalar input,
            LFLLMembership<InputTermsType::tupleSize>& result)
        {
            result.setVal(I-1, terms->get<I-1>()->membership(input));
            Iterator<I-1>::iterate(terms, input, result);
        }
    };

    template <>
    struct Iterator<0>
    {
        static void iterate(
             const InputTermsType*,
             scalar,
             LFLLMembership<InputTermsType::tupleSize>&)
        {}
    };


private:
    const InputTermsType* m_terms;
};

/************************************************************************/
/* Template methods                                                     */
/************************************************************************/


template <class InputTermsType>
inline LFLLInputFuzzifier<InputTermsType>::
    LFLLInputFuzzifier(const InputTermsType& terms)
    : m_terms(&terms)
{}


template <class InputTermsType>
inline LFLLMembership<InputTermsType::tupleSize>
    LFLLInputFuzzifier<InputTermsType>::fuzzifyVariable(
        scalar input) const
{
    LFLLMembership<InputTermsType::tupleSize> result;
    Iterator<InputTermsType::tupleSize>::iterate(m_terms, input, result);
    return result;
}


LFLL_END_NAMESPACE

#endif //LFLLINPUTVARIABLE_H
