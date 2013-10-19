
#include <gtest/gtest.h>

#define ASSERT_LFLL_EQ(val1, val2) \
    ASSERT_NEAR((val1), (val2), ((val1)*0.01f));
