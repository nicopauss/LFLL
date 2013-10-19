#include <lfll/LFLLMath.h>

#include "LFLLTests.h"

using namespace math;

TEST(LFLLMathTest, SRound)
{
    ASSERT_EQ(42, sround<int>(0.42f, 0, 100));
    ASSERT_EQ(42, sround<int>(0.424f, 0, 100));
    ASSERT_EQ(43, sround<int>(0.43f, 0, 100));
    ASSERT_EQ(43, sround<int>(0.425f, 0, 100));
    ASSERT_EQ(MAX_DOM, sround<dom>(1.0f, MIN_DOM, MAX_DOM));
    ASSERT_EQ(MIN_DOM, sround<dom>(0.0f, MIN_DOM, MAX_DOM));
}

TEST(LFLLMathTest, ScalarToDom)
{
    ASSERT_EQ(MIN_DOM, scalarToDom(0.0f));
    ASSERT_EQ(MAX_DOM, scalarToDom(1.0f));
    ASSERT_EQ(MAX_DOM, scalarToDom(1.5f));
    ASSERT_EQ(MAX_DOM, scalarToDom(0.99999999998f));
    ASSERT_EQ((dom)((MIN_DOM + MAX_DOM)/2+1),
        scalarToDom(0.5f));
}

TEST(LFLLMathTest, DomToScalar)
{
    ASSERT_LFLL_EQ(0.0f, domToScalar(MIN_DOM));
    ASSERT_LFLL_EQ(1.0f, domToScalar(MAX_DOM));

    ASSERT_LFLL_EQ(0.5f, domToScalar((MIN_DOM + MAX_DOM)/2));

    ASSERT_LFLL_EQ(1.f/3.f, domToScalar((MIN_DOM + MAX_DOM)/3));

    ASSERT_LFLL_EQ(2.f/3.f,
        domToScalar(
        static_cast<dom>((MIN_DOM + MAX_DOM)*(2.f/3.f))));
}

TEST(LFLLMathTest, IsLessThan)
{
    ASSERT_TRUE(isLessThan(0.4999f, 0.5f));
}


TEST(LFLLMathTest, IsGreaterThan)
{
    ASSERT_TRUE(isGreaterThan(0.5001f, 0.5f));
}


TEST(LFLLMathTest, IsEqualTo)
{
    ASSERT_TRUE(isEqualTo(0.50000001f, 0.5f));
}

TEST(LFLLMathTest, IsLessOrEqualTo)
{
    ASSERT_TRUE(isLessOrEqualTo(0.4999f, 0.5f));
    ASSERT_TRUE(isLessOrEqualTo(0.50000001f, 0.5f));
}

TEST(LFLLMathTest, IsGreaterOrEqualTo)
{
    ASSERT_TRUE(isGreaterOrEqualTo(0.5001f, 0.5f));
    ASSERT_TRUE(isGreaterOrEqualTo(0.50000001f, 0.5f));
}
