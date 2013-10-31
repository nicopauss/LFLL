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
#include <lfll/engine/LFLLStaticAssert.h>

LFLL_BEGIN_NAMESPACE

enum LFLLSugenoDefuzzifyMethod {
    LFLLSugenoWeightedAverage,
    LFLLSugenoWeightedSum
};

LFLL_END_NAMESPACE

#include <lfll/sugeno/detail/LFLLSugenoDefuzzifierDetail.h>

LFLL_BEGIN_NAMESPACE

/**
  * Sugeno defuzzifier
  */
template <class TermTuple,
    LFLLSugenoDefuzzifyMethod D = LFLLSugenoWeightedAverage>
class LFLLSugenoDefuzzifier
{
public:
    LFLLSugenoDefuzzifier(const TermTuple& terms)
        : m_impl(terms)
    {}

    template <size_t NR>
    scalar defuzzifyConsequence(
        const scalar inputs[],
        const LFLLConsequence<NR>& consequence) const
    {
        return m_impl.defuzzifyConsequence(inputs, consequence);
    }

private:
    const detail::LFLLSugenoDefuzzifierImpl<TermTuple, D> m_impl;
};

LFLL_END_NAMESPACE


#endif //LFLLSUGENODEFUZZIFIER_H
