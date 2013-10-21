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
#include <lfll/LFLLMath.h>
#include <lfll/LFLLMembership.h>
#include <lfll/LFLLRulesEngine.h>
#include <lfll/LFLLMinOperator.h>
#include <lfll/LFLLMaxOperator.h>
#include <lfll/LFLLComplementOperator.h>

#include "LFLLTests.h"

using namespace math;

TEST(LFLLRulesEngineTest, RulesEngine)
{
    const size_t NI = 2;
    const size_t NR = 3;
    const size_t NO = 2;

    // Initialisation



    LFLLRules<NI, NR, NO> rules = {
        {
            // Rule 1
            {
                {1, 2}, {1, 0}, 1.f, false
            },

            // Rule 2
            {
                {-2, 1}, {2, 1}, 1.f, false
            },

            //Rule 3
            {
                {3, 2}, {0, -1}, .5f, true
            }
        }
    };



    LFLLRulesEngine<NI, NR, NO> rulesEngine(rules);

    // Work time

    LFLLMembership<3> degrees1;
    LFLLMembership<2> degrees2;
    LFLLConsequence<NR, 2> consequence1;
    LFLLConsequence<NR, 2> consequence2;

    const LFLLMembershipBase* antecedents[NI] = {
        &degrees1, &degrees2
    };
    LFLLConsequenceBase* consequences[NO] = {
        &consequence1, &consequence2
    };

    degrees1[0] = scalarToDom(0.48f);
    degrees1[1] = scalarToDom(0.09f);
    degrees1[2] = scalarToDom(0.f);

    degrees2[0] = scalarToDom(0.56f);
    degrees2[1] = scalarToDom(0.16f);

    rulesEngine.applyRules(antecedents, consequences);

    dom valPart = DOM_DIFF - (dom)(degrees2[1]/2.f + 0.5f);

    ASSERT_EQ(consequence1.membershipValue(0, 0), scalarToDom(0.16f));
    ASSERT_EQ(consequence1.membershipValue(0, 1), scalarToDom(0.f));
    ASSERT_EQ(consequence1.membershipValue(0, 2), scalarToDom(0.f));

    ASSERT_EQ(consequence1.membershipValue(1, 0), scalarToDom(0.f));
    ASSERT_EQ(consequence1.membershipValue(1, 1), scalarToDom(0.56f));
    ASSERT_EQ(consequence1.membershipValue(1, 2), scalarToDom(0.f));

    ASSERT_EQ(consequence2.membershipValue(0, 0), scalarToDom(0.f));
    ASSERT_EQ(consequence2.membershipValue(0, 1), scalarToDom(0.56f));
    ASSERT_EQ(consequence2.membershipValue(0, 2), valPart);

    ASSERT_EQ(consequence2.membershipValue(1, 0), scalarToDom(0.f));
    ASSERT_EQ(consequence2.membershipValue(1, 1), scalarToDom(0.f));
    ASSERT_EQ(consequence2.membershipValue(1, 2), scalarToDom(0.f));

}
