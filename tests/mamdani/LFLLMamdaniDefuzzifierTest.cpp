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

static const lfll_uint TestDivisions = 10000;


TEST(LFLLMamdaniDefuzzifier, TestCentroidMinMax)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLTriangle o1(0.0f, 0.3f, 1.0f);
    LFLLTriangle o2(0.0f, 0.6f, 1.0f);


    typedef LFLLTuple<LFLLTriangle, LFLLTriangle>
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLMamdaniDefuzzifier<OutputTermTuple, LFLLMamdaniCentroid, 
        LFLLMin, LFLLMax> 
        defuzzifier(outputTerms, 0.0f, 1.0f, TestDivisions);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_REL_EQ(0.521078431372555f, ret);
}

TEST(LFLLMamdaniDefuzzifier, TestCentroidProb)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLTriangle o1(0.0f, 0.3f, 1.0f);
    LFLLTriangle o2(0.0f, 0.6f, 1.0f);


    typedef LFLLTuple<LFLLTriangle, LFLLTriangle>
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLMamdaniDefuzzifier<OutputTermTuple, LFLLMamdaniCentroid, 
        LFLLProbabilisticProduct, LFLLProbabilisticSum> 
        defuzzifier(outputTerms, 0.0f, 1.0f, TestDivisions);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_REL_EQ(0.512889616875108f, ret);
}


TEST(LFLLMamdaniDefuzzifier, TestBisector)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLTriangle o1(0.0f, 0.3f, 1.0f);
    LFLLTriangle o2(0.0f, 0.6f, 1.0f);


    typedef LFLLTuple<LFLLTriangle, LFLLTriangle>
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLMamdaniDefuzzifier<OutputTermTuple, LFLLMamdaniBisector, 
        LFLLMin, LFLLMax> 
        defuzzifier(outputTerms, 0.0f, 1.0f, TestDivisions);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_REL_EQ(0.531249765624883f, ret);
}

TEST(LFLLMamdaniDefuzzifier, TestMeanOfMaximum)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLTriangle o1(0.0f, 0.3f, 1.0f);
    LFLLTriangle o2(0.0f, 0.6f, 1.0f);


    typedef LFLLTuple<LFLLTriangle, LFLLTriangle>
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLMamdaniDefuzzifier<OutputTermTuple, LFLLMamdaniMeanOfMaximum, 
        LFLLMin, LFLLMax> 
        defuzzifier(outputTerms, 0.0f, 1.0f, TestDivisions);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_REL_EQ(0.575f, ret);
}


TEST(LFLLMamdaniDefuzzifier, TestSmallestOfMaximum)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLTriangle o1(0.0f, 0.3f, 1.0f);
    LFLLTriangle o2(0.0f, 0.6f, 1.0f);


    typedef LFLLTuple<LFLLTriangle, LFLLTriangle>
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLMamdaniDefuzzifier<OutputTermTuple, LFLLMamdaniSmallestOfMaximum, 
        LFLLMin, LFLLMax> 
        defuzzifier(outputTerms, 0.0f, 1.0f, TestDivisions);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_REL_EQ(0.45f, ret);
}


TEST(LFLLMamdaniDefuzzifier, TestLargestOfMaximum)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLTriangle o1(0.0f, 0.3f, 1.0f);
    LFLLTriangle o2(0.0f, 0.6f, 1.0f);


    typedef LFLLTuple<LFLLTriangle, LFLLTriangle>
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLMamdaniDefuzzifier<OutputTermTuple, LFLLMamdaniLargestOfMaximum, 
        LFLLMin, LFLLMax> 
        defuzzifier(outputTerms, 0.0f, 1.0f, TestDivisions);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);


    scalar ret = defuzzifier.defuzzifyConsequence(consequence);

    ASSERT_LFLL_REL_EQ(0.70f, ret);
}



