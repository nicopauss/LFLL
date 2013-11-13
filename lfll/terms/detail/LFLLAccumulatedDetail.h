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
#ifndef LFLLACCUMULATEDDETAIL_H
#define LFLLACCUMULATEDDETAIL_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLTuple.h>

LFLL_BEGIN_NAMESPACE

namespace detail 
{


template <size_t I, class TermTuple, class SNorm>
struct LFLLAccumulatedImplIterator
{
    inline static scalar membership(
        const TermTuple* terms,
        const SNorm& sNorm,
        const scalar x)
    {
        const scalar prevMembership = 
            LFLLAccumulatedImplIterator<I-1, TermTuple, SNorm>::
                membership(terms, sNorm, x);
        const scalar currentMembership = 
            getLFLLTuple<I-1>(*terms)->membership(x);
        return sNorm(prevMembership, currentMembership);
    }
};

template <class TermTuple, class SNorm>
struct LFLLAccumulatedImplIterator<0, TermTuple, SNorm>
{
    inline static scalar membership(
        const TermTuple*,
        const SNorm&,
        const scalar)
    {
        return ZERO_SCALAR;
    }
};




template <class TermTuple, class SNorm>
class LFLLAccumulatedImpl
{
public:
    LFLLAccumulatedImpl(const TermTuple& terms)
        : m_terms(&terms)
        , m_sNorm()
    {}

    inline scalar membership(const scalar x) const
    {
        return LFLLAccumulatedImplIterator<TermTuple::tupleSize, TermTuple, SNorm>::
                membership(m_terms, m_sNorm, x);
    }

private:
    const TermTuple* m_terms;
    const SNorm m_sNorm;
};





}

LFLL_END_NAMESPACE

#endif //LFLLACCUMULATEDDETAIL_H
