#ifndef LFLLMEMBERSHIPGROUP_H
#define LFLLMEMBERSHIPGROUP_H

#include "LFLLMembership.h"

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
