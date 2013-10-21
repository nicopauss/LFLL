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
