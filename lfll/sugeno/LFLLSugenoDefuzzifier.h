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


#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLConsequence.h>
#include <lfll/engine/LFLLArray.h>

LFLL_BEGIN_NAMESPACE

/**
 * \brief Sugeno defuzzify methods
 */
enum LFLLSugenoDefuzzifyMethod {
    LFLLSugenoWeightedAverage, //< Weighted average
    LFLLSugenoWeightedSum //< Weighted sum
};

LFLL_END_NAMESPACE

#include <lfll/sugeno/detail/LFLLSugenoDefuzzifierDetail.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief Sugeno defuzzifier
  * \tparam TermTuple Tuple of terms type
  * \tparam D Defuzzify method (enum LFLLSugenoDefuzzifyMethod), default is Weighted average
  *
  * \see LFLLSugenoDefuzzifyMethod
  * \see LFLLSugenoZeroOrderTerm
  * \see LFLLSugenoFirstOrderTerm
  *
  * \warning This class holds a pointer to the input terms and tuple. So the terms 
  * variables and tuple must have the same or greater lifespan than this object.
  */
template <class TermTuple,
    LFLLSugenoDefuzzifyMethod D = LFLLSugenoWeightedAverage>
class LFLLSugenoDefuzzifier
{
public:
	/**
	 * \brief Constructor
	 * \param terms Tuple of terms
	 * 
 	 * \warning This class holds a pointer to the input terms and tuple. So the terms 
     * variables and tuple must have the same or greater lifespan than this object.
	 */
    LFLLSugenoDefuzzifier(const TermTuple& terms)
        : m_impl(terms)
    {}

	/**
	 * \brief Defuzzify consequence using inputs
	 * \param inputs Inputs
	 * \param consequence Consequence to defuzzify
	 */
    template <size_t NI, size_t NR>
    scalar defuzzifyConsequence(
        const LFLLArray<NI>& inputs,
        const LFLLConsequence<NR>& consequence) const
    {
        return m_impl.defuzzifyConsequence(inputs, consequence);
    }

private:
    const detail::LFLLSugenoDefuzzifierImpl<TermTuple, D> m_impl;
};

/**
  * \example sugeno/SugenoAllTerms.h
  * \example sugeno/SugenoAllTerms.cpp
  */

LFLL_END_NAMESPACE


#endif //LFLLSUGENODEFUZZIFIER_H
