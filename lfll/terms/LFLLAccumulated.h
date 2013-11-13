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
#ifndef LFLLACCUMULATED_H
#define LFLLACCUMULATED_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/norms/LFLLSNorm.h>
#include <lfll/terms/detail/LFLLAccumulatedDetail.h>

LFLL_BEGIN_NAMESPACE


/**
  * \brief Accumulated term.
  *
  * Accumulate multiple term using a tuple of terms and an SNorm operator
  */
template <class TermTuple, class SNorm = LFLLMax>
class LFLLAccumulated
{
public:
    LFLLAccumulated(const TermTuple& terms)
        : m_impl(terms)
    {}

    inline scalar membership(const scalar x) const
    {
        return m_impl.membership(x);
    }

private:
    const detail::LFLLAccumulatedImpl<TermTuple, SNorm> m_impl;
};

LFLL_END_NAMESPACE

#endif //LFLLACCUMULATED_H
