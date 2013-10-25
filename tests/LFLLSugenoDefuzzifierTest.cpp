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
/*

TEST(LFLLSugenoDefuzzifierTest, Test1)
{
    const size_t NR = 3;
    const size_t NT = 2;

    scalar inputs[3] = {0.f, 0.4f, 5.f};

    const LFLLSugenoCrispValues<NT> crispValues = {{
        0.5f,
        1.0f
    }};

    LFLLSugenoDefuzzifier<NR, NT> defuzzifier(crispValues);


    LFLLConsequence<NR, NT> consequence;

    consequence.getVal(0, 0) = 0.25f;
    consequence.getVal(0, 1) = 0.f;
    consequence.getVal(0, 2) = 0.f;

    consequence.getVal(1, 0) = 0.f;
    consequence.getVal(1, 1) = 0.75f;
    consequence.getVal(1, 2) = 0.10f;


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_EQ(0.886f, ret);
}

TEST(LFLLSugenoDefuzzifierTest, Test2)
{
    const size_t NR = 3;
    const size_t NT = 2;

    const LFLLSugenoCrispValues<NT> crispValues = {{
        0.1f,
        40.0f
    }};

    LFLLSugenoDefuzzifier<NR, NT> defuzzifier(crispValues);


    LFLLConsequence<NR, NT> consequence;

    consequence.getVal(0, 0) = 0.60f;
    consequence.getVal(0, 1) = 0.50f;
    consequence.getVal(0, 2) = 0.f;

    consequence.getVal(1, 0) = 0.f;
    consequence.getVal(1, 1) = 0.f;
    consequence.getVal(1, 2) = 1.f/3.f;


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_EQ(9.38f, ret);
}
*/
