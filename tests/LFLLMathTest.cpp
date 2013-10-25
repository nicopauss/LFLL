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
#include "LFLLTests.h"

using namespace math;

TEST(LFLLMathTest, Srel)
{
    ASSERT_EQ(42.f, srel(0.42f, 0.f, 100.f));
    ASSERT_EQ(75.f, srel(0.5f, 50.f, 100.f));
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
