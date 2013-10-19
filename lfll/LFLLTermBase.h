#ifndef LFLLTERMBASE_H
#define LFLLTERMBASE_H

#include "LFLLDefinitions.h"

LFLL_BEGIN_NAMESPACE

/**
  * Base of terms
  */
class LFLLTermBase
{
public:
    virtual dom membership(scalar val) const = 0;
};


class LFLLBoundedTerm : public LFLLTermBase
{
public:
    LFLLBoundedTerm(scalar minLimit, scalar maxLimit)
        : m_minLimit(minLimit)
        , m_maxLimit(maxLimit)
    {}

    inline scalar getMinLimit() const
    {
        return m_minLimit;
    }

    inline scalar getMaxLimit() const
    {
        return m_maxLimit;
    }

protected:
    scalar m_minLimit;
    scalar m_maxLimit;
};

template <size_t NT>
struct LFLLTerms
{
    const LFLLTermBase* terms[NT];
};

LFLL_END_NAMESPACE



#endif //LFLLTERMBASE_H
