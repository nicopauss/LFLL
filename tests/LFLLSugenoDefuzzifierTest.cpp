#include <lfll/LFLLSugenoDefuzzifier.h>

#include "LFLLTests.h"

using namespace math;

TEST(LFLLSugenoDefuzzifierTest, Test1)
{
    const size_t NR = 3;
    const size_t NT = 2;

    const LFLLSugenoCrispValues<NT> crispValues = {{
        0.5f,
        1.0f
    }};

    LFLLSugenoDefuzzifier<NR, NT> defuzzifier(crispValues);


    LFLLConsequence<NR, NT> consequence;

    consequence.membershipValue(0, 0) = scalarToDom(0.25f);
    consequence.membershipValue(0, 1) = scalarToDom(0.f);
    consequence.membershipValue(0, 2) = scalarToDom(0.f);

    consequence.membershipValue(1, 0) = scalarToDom(0.f);
    consequence.membershipValue(1, 1) = scalarToDom(0.75f);
    consequence.membershipValue(1, 2) = scalarToDom(0.10f);


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_EQ(0.886f, ret);
}

TEST(LFLLSugenoDefuzzifierTest, Test2)
{
    const size_t NR = 3;
    const size_t NT = 2;

    const LFLLSugenoCrispValues<NT> crispValues = {{
        0.1f,
        40.0f
    }};

    LFLLSugenoDefuzzifier<NR, NT> defuzzifier(crispValues);


    LFLLConsequence<NR, NT> consequence;

    consequence.membershipValue(0, 0) = scalarToDom(0.60f);
    consequence.membershipValue(0, 1) = scalarToDom(0.50f);
    consequence.membershipValue(0, 2) = scalarToDom(0.f);

    consequence.membershipValue(1, 0) = scalarToDom(0.f);
    consequence.membershipValue(1, 1) = scalarToDom(0.f);
    consequence.membershipValue(1, 2) = scalarToDom(1.f/3.f);


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_EQ(9.38f, ret);
}
