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

enum LFLLMamdaniDefuzzifyMethod {
    LFLLMamdaniCentroid,
    LFLLMamdaniBisector,
    LFLLMamdaniMeanOfMaximum,
    LFLLMamdaniSmallestOfMaximum,
    LFLLMamdaniLargestOfMaximum
};

LFLL_END_NAMESPACE

#include <lfll/mamdani/detail/LFLLMamdaniCentroidDefuzzifier.h>

LFLL_BEGIN_NAMESPACE

/**
  * Mamdani defuzzifier
  */
template <class TermTuple,
    LFLLMamdaniDefuzzifyMethod D = LFLLMamdaniCentroid,
    class ImpMethod = LFLLMin,
    class AggMethod = LFLLMax>
class LFLLMamdaniDefuzzifier
{
public:
    static const lfll_uint DefaultDivisions = 200;

public:
    LFLLMamdaniDefuzzifier(
        const TermTuple& terms, 
        scalar minRange, scalar maxRange, 
        lfll_uint divisions = DefaultDivisions,
        ImpMethod impMethod = ImpMethod(),
        AggMethod aggMethod = AggMethod())
        : m_impl(terms, minRange, maxRange, divisions, impMethod, aggMethod)
    {}

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

LFLL_END_NAMESPACE


#endif //LFLLMAMDANIDEFUZZIFIER_H
