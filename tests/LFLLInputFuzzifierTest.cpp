
#include <lfll/LFLLPiShape.h>
#include <lfll/LFLLTrapezoid.h>
#include <lfll/LFLLTriangle.h>
#include <lfll/LFLLRectangle.h>
#include <lfll/LFLLSingleton.h>

#include <lfll/LFLLInputFuzzifier.h>

#include "LFLLTests.h"

using namespace math;

TEST(LFLLInputFuzzifierTest, Test1)
{
    LFLLPiShape piShape(0.f, 2.5f, 7.5f, 10.f);
    LFLLTrapezoid trapezoid(0.f, 2.5f, 7.5f, 10.f);
    LFLLTriangle triangle(0.f, 5.f, 10.f);
    LFLLRectangle rectangle(2.5f, 9.f);
    LFLLSingleton singleton(1.64f);

    const LFLLTerms<5> inputTerms = {{
        &piShape, &trapezoid, &triangle, &rectangle, &singleton
    }};

    const LFLLInputFuzzifier<5> inputFuzzifier(inputTerms);

    LFLLMembership<5> degrees =
        inputFuzzifier.fuzzifyVariable(1.64f);

    scalar s1 = domToScalar(degrees[0]);
    scalar s2 = domToScalar(degrees[1]);
    scalar s3 = domToScalar(degrees[2]);
    scalar s4 = domToScalar(degrees[3]);
    scalar s5 = domToScalar(degrees[4]);

    ASSERT_LFLL_EQ(0.763f, s1);
    ASSERT_LFLL_EQ(0.656f, s2);
    ASSERT_LFLL_EQ(0.328f, s3);
    ASSERT_LFLL_EQ(0.0f, s4);
    ASSERT_LFLL_EQ(1.0f, s5);
}


TEST(LFLLInputFuzzifierTest, Test2)
{
    LFLLPiShape piShape(0.f, 2.5f, 7.5f, 10.f);
    LFLLTrapezoid trapezoid(0.f, 2.5f, 7.5f, 10.f);
    LFLLTriangle triangle(0.f, 5.f, 10.f);
    LFLLRectangle rectangle(2.5f, 9.f);
    LFLLSingleton singleton(1.64f);

    const LFLLTerms<5> inputTerms = {{
        &piShape, &trapezoid, &triangle, &rectangle, &singleton
    }};

    const LFLLInputFuzzifier<5> inputFuzzifier(inputTerms);

    LFLLMembership<5> degrees =
        inputFuzzifier.fuzzifyVariable(8.47f);

    scalar s1 = domToScalar(degrees[0]);
    scalar s2 = domToScalar(degrees[1]);
    scalar s3 = domToScalar(degrees[2]);
    scalar s4 = domToScalar(degrees[3]);
    scalar s5 = domToScalar(degrees[4]);

    ASSERT_LFLL_EQ(0.699f, s1);
    ASSERT_LFLL_EQ(0.612f, s2);
    ASSERT_LFLL_EQ(0.306f, s3);
    ASSERT_LFLL_EQ(1.0f, s4);
    ASSERT_LFLL_EQ(0.0f, s5);
}

