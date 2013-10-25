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

TEST(LFLLZShapeTest, ZShape)
{
    LFLLZShape zshape(0.0f, 10.f);
    scalar d1, d2, d3, d4, d5, d6, d7, d8, d9;

    d1 = zshape.membership(2.15f);
    d2 = zshape.membership(5.61f);
    d3 = zshape.membership(7.48f);
    d4 = zshape.membership(0.0f);
    d5 = zshape.membership(10.2f);
    d6 = zshape.membership(4.99f);
    d7 = zshape.membership(5.f);
    d8 = zshape.membership(5.01f);
    d9 = zshape.membership(5.10f);

    ASSERT_LFLL_EQ(0.908f, d1);
    ASSERT_LFLL_EQ(0.385f, d2);
    ASSERT_LFLL_EQ(0.127f, d3);
    ASSERT_LFLL_EQ(1.0f, d4);
    ASSERT_LFLL_EQ(0.0f, d5);
    ASSERT_LFLL_EQ(0.502f, d6);
    ASSERT_LFLL_EQ(0.5f, d7);
    ASSERT_LFLL_EQ(0.498f, d8);
    ASSERT_LFLL_EQ(0.480f, d9);

}
