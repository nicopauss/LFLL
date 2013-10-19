#include <lfll/LFLLZShape.h>
#include <lfll/LFLLMath.h>

#include "LFLLTests.h"

using namespace math;

TEST(LFLLZShapeTest, ZShape)
{
    LFLLZShape zshape(0.0f, 10.f);
    dom d1, d2, d3, d4, d5, d6, d7, d8, d9;
    scalar s1, s2, s3, s4, s5, s6, s7, s8, s9;

    d1 = zshape.membership(2.15f);
    d2 = zshape.membership(5.61f);
    d3 = zshape.membership(7.48f);
    d4 = zshape.membership(0.0f);
    d5 = zshape.membership(10.2f);
    d6 = zshape.membership(4.99f);
    d7 = zshape.membership(5.f);
    d8 = zshape.membership(5.01f);
    d9 = zshape.membership(5.10f);

    s1 = domToScalar(d1);
    s2 = domToScalar(d2);
    s3 = domToScalar(d3);
    s4 = domToScalar(d4);
    s5 = domToScalar(d5);
    s6 = domToScalar(d6);
    s7 = domToScalar(d7);
    s8 = domToScalar(d8);
    s9 = domToScalar(d9);

    ASSERT_LFLL_EQ(0.908f, s1);
    ASSERT_LFLL_EQ(0.385f, s2);
    ASSERT_LFLL_EQ(0.127f, s3);
    ASSERT_LFLL_EQ(1.0f, s4);
    ASSERT_LFLL_EQ(0.0f, s5);
    ASSERT_LFLL_EQ(0.502f, s6);
    ASSERT_LFLL_EQ(0.5f, s7);
    ASSERT_LFLL_EQ(0.498f, s8);
    ASSERT_LFLL_EQ(0.480f, s9);

}
