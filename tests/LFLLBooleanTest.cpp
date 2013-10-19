#include <lfll/LFLLBoolean.h>
#include <lfll/LFLLMath.h>

#include "LFLLTests.h"

TEST(LFLLBooleanTest, Test1)
{
    LFLLBoolean booleanLFLL(true);

    ASSERT_EQ(MAX_DOM, booleanLFLL.membership(true));
}


TEST(LFLLBooleanTest, Test2)
{
    LFLLBoolean booleanLFLL(true);

    ASSERT_EQ(MIN_DOM, booleanLFLL.membership(false));
}

TEST(LFLLBooleanTest, Test3)
{
    LFLLBoolean booleanLFLL(false);

    ASSERT_EQ(MIN_DOM, booleanLFLL.membership(true));
}


TEST(LFLLBooleanTest, Test4)
{
    LFLLBoolean booleanLFLL(false);

    ASSERT_EQ(MAX_DOM, booleanLFLL.membership(false));
}
