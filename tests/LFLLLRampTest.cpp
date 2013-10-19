#include <lfll/LFLLLRamp.h>
#include <lfll/LFLLMath.h>

#include "LFLLTests.h"

using namespace math;

TEST(LFLLLRampTest, LRamp)
{
    LFLLLRamp rRamp(0.0f, 10.f);
    dom d1, d2, d3, d4, d5;
    scalar s1, s2, s3, s4, s5;

    d1 = rRamp.membership(2.15f);
    d2 = rRamp.membership(5.61f);
    d3 = rRamp.membership(7.48f);
    d4 = rRamp.membership(0.0f);
    d5 = rRamp.membership(10.2f);

    s1 = domToScalar(d1);
    s2 = domToScalar(d2);
    s3 = domToScalar(d3);
    s4 = domToScalar(d4);
    s5 = domToScalar(d5);

    ASSERT_LFLL_EQ(0.785f, s1);
    ASSERT_LFLL_EQ(0.439f, s2);
    ASSERT_LFLL_EQ(0.252f, s3);
    ASSERT_LFLL_EQ(1.0f, s4);
    ASSERT_LFLL_EQ(0.0f, s5);
}
