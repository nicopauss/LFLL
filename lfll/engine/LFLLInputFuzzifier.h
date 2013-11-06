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
#ifndef LFLLINPUTFUZZIFIER_H
#define LFLLINPUTFUZZIFIER_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLMembership.h>

#include <lfll/engine/detail/LFLLInputFuzzifierDetail.h>

LFLL_BEGIN_NAMESPACE


/**
 * \brief Fuzzify inputs to membership.
 * 
 * \tparam InputTermsType Tuple type of inputs
 * \warning This class holds a pointer to the input terms and tuple. So the terms 
 * and tuple variables must have the same or greater lifespan than this object.
 */
template <class InputTermsType>
class LFLLInputFuzzifier {
public:
    /**
     * \brief Constructor
     * \param terms Tuple of input terms.
 	 * \warning This class holds a pointer to the input terms and tuple. So the terms 
     * variables and tuple must have the same or greater lifespan than this object.
     */
    LFLLInputFuzzifier(const InputTermsType& terms)
		: m_impl(terms)
	{}

	/**
	 * \brief Fuzzify input.
	 * \return Membership of fuzzified input.
	 */
    LFLLMembership<InputTermsType::tupleSize>
            fuzzifyVariable(scalar input) const
	{
		return m_impl.fuzzifyVariable(input);
	}

private:
    const detail::LFLLInputFuzzifierImpl<InputTermsType> m_impl;
};

LFLL_END_NAMESPACE

#endif //LFLLINPUTFUZZIFIER_H
