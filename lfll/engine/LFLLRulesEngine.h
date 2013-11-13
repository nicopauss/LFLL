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
#ifndef LFLLRULESENGINE_H
#define LFLLRULESENGINE_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLRule.h>
#include <lfll/norms/LFLLSNorm.h>
#include <lfll/norms/LFLLTNorm.h>
#include <lfll/norms/LFLLCNorm.h>
#include <lfll/engine/LFLLStaticAssert.h>
#include <lfll/engine/detail/LFLLRulesEngineDetail.h>


LFLL_BEGIN_NAMESPACE

/**
  * \brief Apply rules.
  *
  * \tparam NI Number of input variables
  * \tparam NR Number of rules
  * \tparam NO Number of output variables
  * \tparam AndOperator T-Norm operator defining the AND operator, default is Min
  * \tparam OrOperator S-Norm operator defining the OR operator, default is Max
  * \tparam NotOperator C-Norm operator defining the NOT operator, default is Not
  *
  * \warning This class holds a pointer to the rules. So the rules 
  * variable must have the same or greater lifespan than this object.
  */
template<size_t NI,
         size_t NR,
         size_t NO,
         class AndOperator = LFLLMin,
         class OrOperator = LFLLMax,
         class NotOperator = LFLLNot>
class LFLLRulesEngine
{
public:
	/**
	 * \brief Constructor
	 * \param rules The rules
	 * \param andOp AND operator. Value is passed by copy.
	 * \param orOp OR operator. Value is passed by copy.
	 * \param notOp NOT operator. Value is passed by copy.
	 * 
 	 * \warning This class holds a pointer to the rules. So the rules 
     * variable must have the same or greater lifespan than this object.
	 */
    LFLLRulesEngine(
        const LFLLRules<NI, NR, NO>& rules,
        AndOperator andOp = AndOperator(),
        OrOperator orOp = OrOperator(),
        NotOperator notOp = NotOperator())
        : m_impl(rules)
        , m_andOp(andOp)
        , m_orOp(orOp)
        , m_notOp(notOp)
    {}

	/**
	 * \brief Apply rules
	 * \param antecedents Antecedents input
	 * \param consequences Consequences output
	 */
    template <class AntecedentTuple, class ConsequenceTuple>
    void applyRules(
        const AntecedentTuple& antecedents,
        ConsequenceTuple& consequences) const
    {
        LFLL_STATIC_ASSERT(
            AntecedentTuple::tupleSize == NI,
            antecedents_size_is_not_valid);
        LFLL_STATIC_ASSERT(
            ConsequenceTuple::tupleSize == NO,
            antecedents_size_is_not_valid);

        m_impl.applyRules(antecedents, consequences, m_andOp, m_orOp, m_notOp);
    }

private:
    const detail::LFLLRulesEngineImpl<NR, NI, NR, NO,
        AndOperator, OrOperator, NotOperator> m_impl;
    const AndOperator m_andOp;
    const OrOperator m_orOp;
    const NotOperator m_notOp;
};


LFLL_END_NAMESPACE


#endif //LFLLRULESENGINE_H
