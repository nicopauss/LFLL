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
#ifndef LFLLMAMDANIDEFUZZIFIER_H
#define LFLLMAMDANIDEFUZZIFIER_H


#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLConsequence.h>
#include <lfll/norms/LFLLSNorm.h>
#include <lfll/norms/LFLLTNorm.h>

LFLL_BEGIN_NAMESPACE

/**
 * \brief Mamdani defuzzify methods
 */
enum LFLLMamdaniDefuzzifyMethod {
    LFLLMamdaniCentroid, //< Centroid
    LFLLMamdaniBisector, //< Bisector
    LFLLMamdaniMeanOfMaximum, //< Mean of maximum
    LFLLMamdaniSmallestOfMaximum, //< Smallest of maximum
    LFLLMamdaniLargestOfMaximum //< Largest of maximum
};

LFLL_END_NAMESPACE

#include <lfll/mamdani/detail/LFLLMamdaniCentroidDefuzzifier.h>
#include <lfll/mamdani/detail/LFLLMamdaniBisectorDefuzzifier.h>
#include <lfll/mamdani/detail/LFLLMamdaniMeanOfMaximumDefuzzifier.h>
#include <lfll/mamdani/detail/LFLLMamdaniSmallestOfMaximumDefuzzifier.h>
#include <lfll/mamdani/detail/LFLLMamdaniLargestOfMaximumDefuzzifier.h>

LFLL_BEGIN_NAMESPACE

/**
  * \brief Mamdani defuzzifier
  * \tparam TermTuple Tuple of terms type
  * \tparam D Defuzzify method (enum LFLLMamdaniDefuzzifyMethod), default is Centroid
  * \tparam ImpMethod T-Norm implication method, default is Min
  * \tparam AggMethod S-Norm aggregation method, default is Max
  *
  * \see LFLLMamdaniDefuzzifyMethod
  *
  * \warning This class holds a pointer to the input terms and tuple. So the terms 
  * variables and tuple must have the same or greater lifespan than this object.
  */
template <class TermTuple,
    LFLLMamdaniDefuzzifyMethod D = LFLLMamdaniCentroid,
    class ImpMethod = LFLLMin,
    class AggMethod = LFLLMax>
class LFLLMamdaniDefuzzifier
{
public:
	/// Default number of divisions
    static const lfll_uint DefaultDivisions = 500;

public:
	/**
	 * \brief Constructor
	 * \param terms Tuple of terms
	 * \param minRange Min range
	 * \param maxRange Max range
	 * \param divisions Number of divisions
	 * \param impMethod Implication operator. Value is passed by copy.
	 * \param aggMethod Aggregation operator. Value is passed by copy.
	 * 
 	 * \warning This class holds a pointer to the input terms and tuple. So the terms 
     * variables and tuple must have the same or greater lifespan than this object.
	 */
    LFLLMamdaniDefuzzifier(
        const TermTuple& terms, 
        scalar minRange, scalar maxRange, 
        lfll_uint divisions = DefaultDivisions,
        ImpMethod impMethod = ImpMethod(),
        AggMethod aggMethod = AggMethod())
        : m_impl(terms, minRange, maxRange, divisions, impMethod, aggMethod)
    {}

	/**
	 * \brief Defuzzify consequence
	 * \param consequence Consequence to defuzzify
	 */
    template <size_t NR>
    scalar defuzzifyConsequence(
        const LFLLConsequence<NR>& consequence) const
    {
        return m_impl.defuzzifyConsequence(consequence);
    }

private:
    typedef typename detail::LFLLMamdaniDefuzzifierMethodType
        <D, TermTuple, ImpMethod, AggMethod>::type DefuzzifierMethod;
    const DefuzzifierMethod m_impl;
};

/**
  * \example mamdani/MamdaniAllTerms.h
  * \example mamdani/MamdaniAllTerms.cpp
  */

LFLL_END_NAMESPACE


#endif //LFLLMAMDANIDEFUZZIFIER_H
