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
  * \brief Consequences from rules.
  * Destined to be defuzzified or aggregated.
  * \tparam NR Number of rules.
  */
template <size_t NR>
class LFLLConsequence
{
public:
    static const size_t nbRules = NR;

private:
    struct RuleConsequence
    {
        lfll_uint termIndex;
        scalar value;
        RuleConsequence() : termIndex(0), value(ZERO_SCALAR) {}
    };

public:
	/**
	 * \brief Default constructor
	 */
    LFLLConsequence()
    {}

	/**
	 * \brief Copy constructor.
	 * \param o An other consequence.
	 */
    LFLLConsequence(const LFLLConsequence<NR>& o)
    {
        std::copy(o.m_values, o.m_values+NR, m_values);
    }

	/**
	 * \brief Copy operator.
	 * \param o An other consequence.
	 */
    LFLLConsequence<NR>& operator=(const LFLLConsequence<NR>& o)
    {
        std::copy(o.m_values, o.m_values+NR, m_values);
        return *this;
    }

	
	/**
	 * \brief Get number of rules.
	 */
    inline size_t getNbRules() const
    {
        return NR;
    }
    
	/**
	 * \brief Get term index for specified rule index.
	 * \param rule Rule index
	 * \return Reference to term index
	 */
    inline lfll_uint& getTermIndex(size_t rule) 
    {
        assert(rule < NR);
        return m_values[rule].termIndex;
    }
    
	/**
	 * \brief Get term index for specified rule index.
	 * \param rule Rule index
	 * \return Term index
	 */
    inline lfll_uint getTermIndex(size_t rule) const
    {
        assert(rule < NR);
        return m_values[rule].termIndex;
    }
    
	/**
	 * \brief Get value for specified rule index.
	 * \param rule Rule index
	 * \return Reference to value
	 */
    inline scalar& getVal(size_t rule)
    {
        assert(rule < NR);
        return m_values[rule].value;
    }
    
	/**
	 * \brief Get value for specified rule index.
	 * \param rule Rule index
	 * \return Value
	 */
    inline scalar getVal(size_t rule) const
    {
        assert(rule < NR);
        return m_values[rule].value;
    }
    
	/**
	 * \brief Set term index for specified rule index.
	 * \param rule Rule index
	 * \param termIndex Term index
	 */
    inline void setTermIndex(size_t rule, lfll_uint termIndex)
    {
        assert(rule < NR);
        m_values[rule].termIndex = termIndex;
    }

	/**
	 * \brief Set value for specified rule index.
	 * \param rule Rule index
	 * \param val Value
	 */
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
