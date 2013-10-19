#ifndef LFLLRULESENGINE_H
#define LFLLRULESENGINE_H

#include "LFLLDefinitions.h"
#include "LFLLMembership.h"
#include "LFLLRule.h"
#include "LFLLConsequence.h"
#include "LFLLMaxOperator.h"
#include "LFLLMinOperator.h"
#include "LFLLComplementOperator.h"
#include "LFLLRulesEngineDetail.h"



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

    void applyRules(
        const LFLLMembershipBase* antecedents[NI],
        LFLLConsequenceBase* consequences[NO]) const;

private:
    const detail::LFLLRulesEngine<NR, NI, NR, NO,
        AndOperator, OrOperator, NotOperator> m_detailEngine;
};





/*************************************************************************/
/* Template methods */
/*************************************************************************/

template<size_t NI, size_t NR, size_t NO,
    class AndOperator, class OrOperator, class NotOperator>
inline LFLLRulesEngine<NI, NR, NO,
    AndOperator, OrOperator, NotOperator>::LFLLRulesEngine(
    const LFLLRules<NI, NR, NO>& rules)
    : m_detailEngine(rules)
{}


template<size_t NI, size_t NR, size_t NO,
    class AndOperator, class OrOperator, class NotOperator>
inline void LFLLRulesEngine<NI, NR, NO,
    AndOperator, OrOperator, NotOperator>::applyRules(
    const LFLLMembershipBase* antecedents[NI],
    LFLLConsequenceBase* consequences[NO]) const
{
    m_detailEngine.applyRules(antecedents, consequences);
}


LFLL_END_NAMESPACE


#endif //LFLLRULESENGINE_H
