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


#include <lfll/LFLLDefinitions.h>
#include <lfll/LFLLConsequence.h>
#include <lfll/LFLLStaticAssert.h>

LFLL_BEGIN_NAMESPACE

enum LFLLSugenoDefuzzifyMethod {
    LFLL_SUGENO_WEIGHTED_AVERAGE,
    LFLL_SUGENO_WEIGHTED_SUM
};

LFLL_END_NAMESPACE

#include <lfll/detail/LFLLSugenoDefuzzifierDetail.h>

LFLL_BEGIN_NAMESPACE

/**
  * Sugeno defuzzifier
  */
template <class TermTuple,
    LFLLSugenoDefuzzifyMethod D = LFLL_SUGENO_WEIGHTED_AVERAGE>
class LFLLSugenoDefuzzifier
{
public:
    LFLLSugenoDefuzzifier(const TermTuple& terms)
        : m_impl(terms)
    {}

    template <size_t NR, size_t NT>
    scalar defuzzifyConsequence(
        const scalar inputs[],
        const LFLLConsequence<NR, NT>& consequence) const
    {
        LFLL_STATIC_ASSERT(NT == TermTuple::tupleSize,
            number_of_term_and_tuple_size_are_not_equal);
        return m_impl.defuzzifyConsequence(inputs, consequence);
    }

private:
    typename detail::LFLLSugenoDefuzzifierType<TermTuple, D>::type m_impl;
};

LFLL_END_NAMESPACE


#endif //LFLLSUGENODEFUZZIFIER_H
