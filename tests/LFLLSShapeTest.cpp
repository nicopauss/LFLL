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
#include <lfll/LFLLSShape.h>
#include <lfll/LFLLMath.h>

#include "LFLLTests.h"

using namespace math;

TEST(ElectronicHorizonLFLLTests, SShape)
{
    LFLLSShape sshape(0.0f, 10.f);
    dom d1, d2, d3, d4, d5, d6, d7, d8, d9;
    scalar s1, s2, s3, s4, s5, s6, s7, s8, s9;

    d1 = sshape.membership(3.5f);
    d2 = sshape.membership(6.4f);
    d3 = sshape.membership(8.4f);
    d4 = sshape.membership(0.0f);
    d5 = sshape.membership(10.2f);
    d6 = sshape.membership(4.99f);
    d7 = sshape.membership(5.f);
    d8 = sshape.membership(5.01f);
    d9 = sshape.membership(5.10f);

    s1 = domToScalar(d1);
    s2 = domToScalar(d2);
    s3 = domToScalar(d3);
    s4 = domToScalar(d4);
    s5 = domToScalar(d5);
    s6 = domToScalar(d6);
    s7 = domToScalar(d7);
    s8 = domToScalar(d8);
    s9 = domToScalar(d9);



    ASSERT_LFLL_EQ(0.245f, s1);
    ASSERT_LFLL_EQ(0.741f, s2);
    ASSERT_LFLL_EQ(0.949f, s3);
    ASSERT_LFLL_EQ(0.0f, s4);
    ASSERT_LFLL_EQ(1.0f, s5);
    ASSERT_LFLL_EQ(0.498f, s6);
    ASSERT_LFLL_EQ(0.5f, s7);
    ASSERT_LFLL_EQ(0.502f, s8);
    ASSERT_LFLL_EQ(0.520f, s9);
}
