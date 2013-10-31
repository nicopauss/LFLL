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
#ifndef LFLLRULE_H
#define LFLLRULE_H

#include <lfll/engine/LFLLDefinitions.h>

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
    lfll_int inputVariables[NI]; //< Input variables.
    lfll_int outputVariables[NO]; //< Output variables.
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
