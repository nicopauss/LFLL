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
 * \brief Represent the degrees of membership for each terms for a variable.
 * 
 * \tparam NT Number of terms.
 */
template <size_t NT>
class LFLLMembership
{
public:
    static const size_t nbTerms = NT;

public:

	/**
	 * \brief Default constructor
	 */
    LFLLMembership()
    {}

	/**
	 * \brief Copy constructor.
	 * \param o An other membership
	 */
    LFLLMembership(const LFLLMembership<NT>& o)
    {
        std::copy(o.m_array, o.m_array+NT, m_array);
    }
    
	/**
	 * \brief Construct membership with external input iterator
	 * \tparam InputIt Iterator type
	 * \param iterator Input iterator
	 */
	template <class InputIt>
    LFLLMembership(const InputIt iterator)
    {
        std::copy(iterator, iterator+NT, m_array);
    }
    
	/**
	 * \brief Copy operator.
	 * \param o An other consequence.
	 */
    LFLLMembership<NT>& operator=(const LFLLMembership<NT>& o)
    {
        std::copy(o.m_array, o.m_array+NT, m_array);
        return *this;
    }
    
	/**
	 * \brief Get number of terms.
	 */
    inline size_t getNbTerms() const
    {
        return NT;
    }

	/**
	 * \brief Get value by index.
	 * \param index Value index
	 * \return Reference to value
	 */
    inline scalar& operator[](size_t index)
    {
        assert(index < NT);
        return m_array[index];
    }

	/**
	 * \brief Get value by index.
	 * \param index Value index
	 * \return Value
	 */
    inline scalar operator[](size_t index) const
    {
        assert(index < NT);
        return m_array[index];
    }

	/**
	 * \brief Get value by index.
	 * \param index Value index
	 * \return Reference to value
	 */
    inline scalar& getVal(size_t index)
    {
        assert(index < NT);
        return m_array[index];
    }

	/**
	 * \brief Get value by index.
	 * \param index Value index
	 * \return Value
	 */
    inline scalar getVal(size_t index) const
    {
        assert(index < NT);
        return m_array[index];
    }

	/**
	 * \brief Set value by index.
	 * \param index Value index
	 * \param val Value
	 */
    inline void setVal(size_t index, scalar val)
    {
        assert(index < NT);
        m_array[index] = val;
    }

	/**
	 * \brief Reset values to ZERO_SCALAR
	 */	
    inline void reset()
    {
    	std::fill_n(m_array, NT, ZERO_SCALAR);
    }

private:
    scalar m_array[NT];
};

LFLL_END_NAMESPACE

#endif //LFLLMEMBERSHIPDEGREES_H
