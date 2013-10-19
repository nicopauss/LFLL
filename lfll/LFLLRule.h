#ifndef LFLLRULE_H
#define LFLLRULE_H

#include "LFLLDefinitions.h"

LFLL_BEGIN_NAMESPACE

/**
  * Represent a fuzzy rule.
  *
  * NI is the number of input variables.
  * NO is the number of output variables.
  *
  * It uses a syntax similar to Matlab fuzzy logic toolbox.
  * For inputVariables and outputVariables,
  * you can use the negative form, -n, to use the
  * NOT operator, and you can use 0 as the any value.
  * @see LFLLRules
  */
template <size_t NI, size_t NO>
struct LFLLRule
{
    int32_t inputVariables[NI]; //< Input variables.
    int32_t outputVariables[NO]; //< Output variables.
    scalar weight; //< Weight of the rule, value between 0.0 and 1.0.
    bool orOperator; //< Use the OR operator instead of AND.
};

/**
  * Combination of rules.
  * NI is the number of input variables.
  * NR is the number of rules.
  * NO is the number of output variables.
  *
  * Can be initialized like an array:
  * \code
  * LFLLRules<2,2,1> rules = {{
  *   {{1, 1}, {1}, 1.f, false},
  *   {{2, 1}, {1}, .5f, false}
  * }};
  * \endcode
  */
template <size_t NI, size_t NR, size_t NO>
struct LFLLRules
{
    LFLLRule<NI, NO> rules[NR];
};

LFLL_END_NAMESPACE


#endif //LFLLRULE_H
