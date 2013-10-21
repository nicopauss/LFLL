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
#ifndef LFLLMEMBERSHIPGROUP_H
#define LFLLMEMBERSHIPGROUP_H

#include <lfll/LFLLMembership.h>

LFLL_BEGIN_NAMESPACE


/**
  * Abstract base of templated consequence.
  */
class LFLLConsequenceBase
{
public:
    virtual size_t getNbTerms() const = 0;
    virtual size_t getNbRules() const = 0;
    virtual LFLLMembershipBase* termMembership(size_t term) = 0;
    virtual const LFLLMembershipBase* termMembership(size_t term) const = 0;
    virtual dom& membershipValue(size_t term, size_t rule) = 0;
    virtual dom membershipValue(size_t term, size_t rule) const = 0;
};


/**
  * Consequences from rules.
  * Destined to be dufuzzified or aggregated.
  */
template <size_t NR, size_t NT>
class LFLLConsequence : public LFLLConsequenceBase
{
public:
    static const size_t nbTerms = NT;
    static const size_t nbRules = NR;
public:

    virtual inline size_t getNbTerms() const
    {
        return NT;
    }

    virtual inline size_t getNbRules() const
    {
        return NR;
    }

    virtual inline LFLLMembershipBase* termMembership(size_t term)
    {
        return &(m_memberships[term]);
    }

    virtual inline const LFLLMembershipBase* termMembership(size_t term) const
    {
        return &(m_memberships[term]);
    }

    virtual inline dom& membershipValue(size_t term, size_t rule)
    {
        return m_memberships[term][rule];
    }

    virtual inline dom membershipValue(size_t term, size_t rule) const
    {
        return m_memberships[term][rule];
    }

private:
    LFLLMembership<NR> m_memberships[NT];
};

LFLL_END_NAMESPACE

#endif //LFLLMEMBERSHIPGROUP_H
