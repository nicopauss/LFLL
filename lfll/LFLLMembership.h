#ifndef LFLLMEMBERSHIPDEGREES_H
#define LFLLMEMBERSHIPDEGREES_H

#include <cstring>
#include <cassert>

#include "LFLLDefinitions.h"

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
