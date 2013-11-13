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
#ifndef LFLLINPUTFUZZIFIERDETAIL_H
#define LFLLINPUTFUZZIFIERDETAIL_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMembership.h>
#include <lfll/engine/LFLLTuple.h>

LFLL_BEGIN_NAMESPACE

namespace detail {

template <class InputTermsType, size_t I>
struct LFLLInputFuzzifierImplIterator
{
	static void iterate(
        const InputTermsType* terms,
        scalar input,
        LFLLMembership<InputTermsType::tupleSize>& result)
    {
        result.setVal(I-1, getLFLLTuple<I-1>(*terms)->membership(input));
        LFLLInputFuzzifierImplIterator<InputTermsType, I-1>::iterate(terms, input, result);
    }
};

template <class InputTermsType>
struct LFLLInputFuzzifierImplIterator<InputTermsType, 0>
{
	static void iterate(
        const InputTermsType*,
        scalar,
        LFLLMembership<InputTermsType::tupleSize>&)
    {}
};


template <class InputTermsType>
class LFLLInputFuzzifierImpl
{
public:

    LFLLInputFuzzifierImpl(const InputTermsType& terms)
		: m_terms(&terms)
	{}

    /**
     * @brief fuzzifyVariable
     * @param input The input variable
     * @return
     */
    LFLLMembership<InputTermsType::tupleSize>
            fuzzifyVariable(scalar input) const
	{
		LFLLMembership<InputTermsType::tupleSize> result;
		LFLLInputFuzzifierImplIterator<InputTermsType, InputTermsType::tupleSize>::
			iterate(m_terms, input, result);
		return result;
	}

private:
    const InputTermsType* m_terms;
};

}
LFLL_END_NAMESPACE

#endif //LFLLINPUTFUZZIFIERDETAIL_H
