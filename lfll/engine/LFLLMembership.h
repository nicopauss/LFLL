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
#ifndef LFLLMEMBERSHIPDEGREES_H
#define LFLLMEMBERSHIPDEGREES_H

#include <cstring>
#include <cassert>

#include <lfll/engine/LFLLDefinitions.h>

LFLL_BEGIN_NAMESPACE


/**
* Represent the degrees of membership for each terms for a variable.
*
* NT define the number of terms.
*/
template <size_t NT>
class LFLLMembership
{
public:
    static const size_t nbTerms = NT;

public:
    LFLLMembership()
    {}

    LFLLMembership(const LFLLMembership<NT>& o)
    {
        memcpy(m_array, o.m_array, sizeof(m_array));
    }

    LFLLMembership(const scalar array[NT])
    {
        memcpy(m_array, array, sizeof(m_array));
    }

    LFLLMembership& operator=(const LFLLMembership<NT>& o)
    {
        memcpy(m_array, o.m_array, sizeof(m_array));
        return *this;
    }

    inline size_t getNbTerms() const
    {
        return NT;
    }

    inline scalar& operator[](size_t index)
    {
        assert(index < NT);
        return m_array[index];
    }

    inline scalar operator[](size_t index) const
    {
        assert(index < NT);
        return m_array[index];
    }

    inline scalar& getVal(size_t index)
    {
        assert(index < NT);
        return m_array[index];
    }

    inline scalar getVal(size_t index) const
    {
        assert(index < NT);
        return m_array[index];
    }

    inline void setVal(size_t index, scalar val)
    {
        assert(index < NT);
        m_array[index] = val;
    }

    inline void reset()
    {
        memset(m_array, 0, sizeof(m_array));
    }

private:
    scalar m_array[NT];
};

LFLL_END_NAMESPACE

#endif //LFLLMEMBERSHIPDEGREES_H
