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
#include "../LFLLTests.h"

using namespace math;

TEST(LFLLInputFuzzifierTest, Test1)
{
    LFLLPiShape piShape(0.f, 2.5f, 7.5f, 10.f);
    LFLLTrapezoid trapezoid(0.f, 2.5f, 7.5f, 10.f);
    LFLLTriangle triangle(0.f, 5.f, 10.f);
    LFLLRectangle rectangle(2.5f, 9.f);
    LFLLSingleton singleton(1.64f);

    typedef LFLLTuple<LFLLPiShape, LFLLTrapezoid,
            LFLLTriangle, LFLLRectangle, LFLLSingleton>
            InputTypes;

    const InputTypes inputTerms = makeLFLLTuple(
        piShape, trapezoid, triangle, rectangle, singleton);

    const LFLLInputFuzzifier<InputTypes> inputFuzzifier(inputTerms);

    LFLLMembership<5> degrees =
        inputFuzzifier.fuzzifyVariable(1.64f);

    ASSERT_LFLL_REL_EQ(0.763328f, degrees[0]);
    ASSERT_LFLL_REL_EQ(0.656f, degrees[1]);
    ASSERT_LFLL_REL_EQ(0.328f, degrees[2]);
    ASSERT_LFLL_REL_EQ(0.0f, degrees[3]);
    ASSERT_LFLL_REL_EQ(1.0f, degrees[4]);
}


TEST(LFLLInputFuzzifierTest, Test2)
{
    LFLLPiShape piShape(0.f, 2.5f, 7.5f, 10.f);
    LFLLTrapezoid trapezoid(0.f, 2.5f, 7.5f, 10.f);
    LFLLTriangle triangle(0.f, 5.f, 10.f);
    LFLLRectangle rectangle(2.5f, 9.f);
    LFLLSingleton singleton(1.64f);

    typedef LFLLTuple<LFLLPiShape, LFLLTrapezoid,
            LFLLTriangle, LFLLRectangle, LFLLSingleton>
            InputTypes;

    const InputTypes inputTerms = makeLFLLTuple(
        piShape, trapezoid, triangle, rectangle, singleton);

    const LFLLInputFuzzifier<InputTypes> inputFuzzifier(inputTerms);

    LFLLMembership<5> degrees =
        inputFuzzifier.fuzzifyVariable(8.47f);

    ASSERT_LFLL_REL_EQ(0.698912f, degrees[0]);
    ASSERT_LFLL_REL_EQ(0.612f, degrees[1]);
    ASSERT_LFLL_REL_EQ(0.306f, degrees[2]);
    ASSERT_LFLL_REL_EQ(1.0f, degrees[3]);
    ASSERT_LFLL_REL_EQ(0.0f, degrees[4]);
}

