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
template <size_t NR>
class LFLLConsequence
{
public:
    static const size_t nbRules = NR;

private:
    /**
      * Consequence from a single rule.
      */
    struct RuleConsequence
    {
        uint32_t termIndex;
        scalar value;
        RuleConsequence() : termIndex(0), value(ZERO_SCALAR) {}
    };

public:
    LFLLConsequence()
    {}

    LFLLConsequence(const LFLLMembership<NT>& o)
    {
        std::copy(o.m_values, o.m_values+NR, m_values);
    }

    LFLLConsequence& operator=(const LFLLConsequence<NT>& o)
    {
        std::copy(o.m_values, o.m_values+NR, m_values);
        return *this;
    }

    inline size_t getNbRules() const
    {
        return NR;
    }

    inline uint32_t& getTermIndex(size_t rule) 
    {
        assert(rule < NR);
        return m_values[rule].termIndex;
    }

    inline uint32_t getTermIndex(size_t rule) const
    {
        assert(rule < NR);
        return m_values[rule].termIndex;
    }

    inline scalar& getVal(size_t rule)
    {
        assert(rule < NR);
        return m_values[rule].value;
    }

    inline scalar getVal(size_t rule) const
    {
        assert(rule < NR);
        return m_values[rule].value;
    }

    inline void setTermIndex(size_t rule, uint32_t termIndex)
    {
        assert(rule < NR);
        m_values[rule].termIndex = termIndex;
    }

    inline void setVal(size_t rule, scalar val)
    {
        assert(rule < NR);
        m_values[rule].value = val;
    }

private:
    RuleConsequence m_values[NR];
};

LFLL_END_NAMESPACE

#endif //LFLLCONSEQUENCE_H
