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
#ifndef LFLLCONSEQUENCE_H
#define LFLLCONSEQUENCE_H

#include <cstring>
#include <cassert>

#include <lfll/engine/LFLLDefinitions.h>

LFLL_BEGIN_NAMESPACE


/**
  * Consequences from rules.
  * Destined to be dufuzzified or aggregated.
  */
template <size_t NR, size_t NT>
class LFLLConsequence
{
public:
    static const size_t nbTerms = NT;
    static const size_t nbRules = NR;

public:
    LFLLConsequence()
    {
        memset(m_values, 0, sizeof(m_values));
    }

    inline size_t getNbTerms() const
    {
        return NT;
    }

    inline size_t getNbRules() const
    {
        return NR;
    }

    inline scalar* operator[](size_t term)
    {
        assert(term < NT);
        return m_values[term];
    }

    inline const scalar* operator[](size_t term) const
    {
        assert(term < NT);
        return m_values[term];
    }

    inline scalar& getVal(size_t term, size_t rule)
    {
        assert(term < NT);
        assert(rule < NR);
        return m_values[term][rule];
    }

    inline scalar getVal(size_t term, size_t rule) const
    {
        assert(term < NT);
        assert(rule < NR);
        return m_values[term][rule];
    }

    inline void setVal(size_t term, size_t rule, scalar val)
    {
        assert(term < NT);
        assert(rule < NR);
        m_values[term][rule] = val;
    }

private:
    scalar m_values[NT][NR];
};

LFLL_END_NAMESPACE

#endif //LFLLCONSEQUENCE_H
