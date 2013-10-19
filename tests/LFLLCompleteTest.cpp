#include <lfll/LFLLMinOperator.h>
#include <lfll/LFLLMaxOperator.h>
#include <lfll/LFLLComplementOperator.h>
#include <lfll/LFLLTriangle.h>
#include <lfll/LFLLInputFuzzifier.h>
#include <lfll/LFLLRulesEngine.h>
#include <lfll/LFLLSugenoDefuzzifier.h>

#include "LFLLTests.h"

using namespace math;

TEST(LFLLCompleteTest, LFLLComplete)
{
    // Creation

    const size_t NI = 2;
    const size_t NTI1 = 3;
    const size_t NTI2 = 2;
    const size_t NR = 6;
    const size_t NO = 1;
    const size_t NTO = 3;

    LFLLTriangle t11(-0.4f, .0f, .3f);
    LFLLTriangle t12(0.05f, .3f, .9f);
    LFLLTriangle t13(0.1f, 1.f, 1.4f);

    LFLLTriangle t21(-0.4f, .0f, .6f);
    LFLLTriangle t22(0.1f, .8f, 1.2f);


    const LFLLTerms<NTI1> inputTerms1 = {{
        &t11, &t12, &t13
    }};

    const LFLLInputFuzzifier<NTI1> inputFuzzifier1(inputTerms1);

    const LFLLTerms<NTI2> inputTerms2 = {{
        &t21, &t22
    }};

    const LFLLInputFuzzifier<NTI2> inputFuzzifier2(inputTerms2);


    LFLLRules<NI, NR, NO> rules = {{
        // Rule 1
        {{1, 1}, {1}, 1.f, false},

        // Rule 2
        {{2, 1}, {1}, 1.f, false},

        // Rule 3
        {{3, 1}, {2}, .5f, false},

        // Rule 4
        {{1, 2}, {1}, 1.f, false},

        // Rule 5
        {{2, 2}, {2}, 1.f, false},

        // Rule 6
        {{3, 2}, {3}, 1.f, false}
    }};

    const LFLLSugenoCrispValues<NTO> crispValues = {{
        0.0f,
        0.75f,
        1.0f
    }};


    LFLLRulesEngine<NI, NR, NO> rulesEngine(rules);

    LFLLSugenoDefuzzifier<NR, NTO> defuzzifier(crispValues);

    // Work

    LFLLMembership<NTI1> degrees1 = inputFuzzifier1.fuzzifyVariable(.2f);
    LFLLMembership<NTI2> degrees2 = inputFuzzifier2.fuzzifyVariable(.3f);

    LFLLConsequence<NR, NTO> consequence;

    const LFLLMembershipBase* antecedents[NI] = {
        &degrees1, &degrees2
    };

    LFLLConsequenceBase* consequences[NO] = {
        &consequence
    };

    rulesEngine.applyRules(antecedents, consequences);

    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    // Test
    ASSERT_LFLL_EQ(0.234f, ret);
}
