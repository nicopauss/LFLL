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

#include <lfll/LFLLDefinitions.h>

LFLL_BEGIN_NAMESPACE

/**
  * Abstract class of templated LFLLMembership
  */
class LFLLMembershipBase
{
public:
    virtual dom& operator[](size_t index) = 0;
    virtual dom operator[](size_t index) const = 0;
    virtual dom getVal(size_t index) const = 0;
    virtual void setVal(size_t index, dom val) = 0;
    virtual size_t getNbTerms() const = 0;
};


/**
* Represent the degrees of membership for each terms for a variable.
*
* NT define the number of terms.
*/
template <size_t NT>
class LFLLMembership : public LFLLMembershipBase
{
    static const size_t nbTerms = NT;

public:
    LFLLMembership()
    {
        memset(m_array, MIN_DOM, sizeof(dom) * NT);
    }

    LFLLMembership(const LFLLMembership<NT>& o)
    {
        memcpy(m_array, o.m_array, sizeof(dom) * NT);
    }

    LFLLMembership(const dom array[NT])
    {
        memcpy(m_array, array, sizeof(dom) * NT);
    }

    LFLLMembership& operator=(const LFLLMembership<NT>& o)
    {
        memcpy(m_array, o.m_array, sizeof(dom) * NT);
        return *this;
    }


    inline dom& operator[](size_t index)
    {
        assert(index < NT);
        return m_array[index];
    }

    inline dom operator[](size_t index) const
    {
        assert(index < NT);
        return m_array[index];
    }

    inline dom getVal(size_t index) const {
        assert(index < NT);
        return m_array[index];
    }

    inline void setVal(size_t index, dom val) {
        assert(index < NT);
        m_array[index] = val;
    }

    inline size_t getNbTerms() const {
        return NT;
    }

private:
    dom m_array[NT];
};

LFLL_END_NAMESPACE

#endif //LFLLMEMBERSHIPDEGREES_H
