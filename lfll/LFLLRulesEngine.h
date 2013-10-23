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

#include <lfll/LFLLDefinitions.h>
#include <lfll/LFLLRule.h>
#include <lfll/LFLLMaxOperator.h>
#include <lfll/LFLLMinOperator.h>
#include <lfll/LFLLComplementOperator.h>
#include <lfll/LFLLStaticAssert.h>
#include <lfll/detail/LFLLRulesEngineDetail.h>


LFLL_BEGIN_NAMESPACE

/**
  * LFLL rules engine.
  *
  * NI is the number of input variables.
  * NR is the number of rules.
  * NO is the number of output variables.
  * AndOperator Binary operator defining the AND operator
  * OrOperator Binary operator defining the OR operator
  * NotOperator Unary operator defining the NOT operator
  */
template<size_t NI,
         size_t NR,
         size_t NO,
         class AndOperator = LFLLMinOperator,
         class OrOperator = LFLLMaxOperator,
         class NotOperator = LFLLComplementOperator>
class LFLLRulesEngine
{
public:
    LFLLRulesEngine(const LFLLRules<NI, NR, NO>& rules);

    template <class AntecedentTuple, class ConsequenceTuple>
    void applyRules(
        const AntecedentTuple& antecedents,
        ConsequenceTuple& consequences) const;

private:
    const detail::LFLLRulesEngineImpl<NR, NI, NR, NO,
        AndOperator, OrOperator, NotOperator> m_impl;
};





/*************************************************************************/
/* Template methods */
/*************************************************************************/

template<size_t NI, size_t NR, size_t NO,
    class AndOperator, class OrOperator, class NotOperator>
inline LFLLRulesEngine<NI, NR, NO,
    AndOperator, OrOperator, NotOperator>::LFLLRulesEngine(
    const LFLLRules<NI, NR, NO>& rules)
    : m_impl(rules)
{}


template<size_t NI, size_t NR, size_t NO,
    class AndOperator, class OrOperator, class NotOperator>
template <class AntecedentTuple, class ConsequenceTuple>
inline void LFLLRulesEngine<NI, NR, NO,
    AndOperator, OrOperator, NotOperator>::applyRules(
    const AntecedentTuple& antecedents,
    ConsequenceTuple& consequences) const
{
    LFLL_STATIC_ASSERT(
        AntecedentTuple::tupleSize == NI,
        antecedents_size_is_not_valid);
    LFLL_STATIC_ASSERT(
        ConsequenceTuple::tupleSize == NO,
        antecedents_size_is_not_valid);

    m_impl.applyRules(antecedents, consequences);
}


LFLL_END_NAMESPACE


#endif //LFLLRULESENGINE_H
