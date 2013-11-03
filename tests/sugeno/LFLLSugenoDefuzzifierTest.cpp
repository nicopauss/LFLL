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


TEST(LFLLSugenoDefuzzifier, TestZeroOrderAverage)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLArray<3> inputs = {0.f, 0.4f, 5.f};

    LFLLSugenoZeroOrderTerm o1 = {0.5f};
    LFLLSugenoZeroOrderTerm o2 = {1.0f};


    typedef LFLLTuple<LFLLSugenoZeroOrderTerm, LFLLSugenoZeroOrderTerm>
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLSugenoDefuzzifier<OutputTermTuple, LFLLSugenoWeightedAverage> 
        defuzzifier(outputTerms);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);


    scalar ret = defuzzifier.defuzzifyConsequence(inputs, consequence);

    ASSERT_LFLL_REL_EQ(0.8863636363636362f, ret);
}


TEST(LFLLSugenoDefuzzifier, TestZeroOrderSum)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLArray<3> inputs = {0.f, 0.4f, 5.f};

    LFLLSugenoZeroOrderTerm o1 = {0.5f};
    LFLLSugenoZeroOrderTerm o2 = {1.0f};


    typedef LFLLTuple<LFLLSugenoZeroOrderTerm, LFLLSugenoZeroOrderTerm>
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLSugenoDefuzzifier<OutputTermTuple, LFLLSugenoWeightedSum> 
        defuzzifier(outputTerms);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);

    scalar ret = defuzzifier.defuzzifyConsequence(inputs, consequence);

    ASSERT_LFLL_REL_EQ(0.975f, ret);
}


TEST(LFLLSugenoDefuzzifier, TestFirstOrderAverage)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLArray<3> inputs = {0.f, 0.4f, 5.f};

    LFLLSugenoFirstOrderTerm<3> o1 = {1.0f, 0.75f, 2.0f, 0.5f};
    LFLLSugenoFirstOrderTerm<3> o2 = {7.0f, 5.0f, 0.25f, 1.0f};


    typedef LFLLTuple<
        LFLLSugenoFirstOrderTerm<3>, 
        LFLLSugenoFirstOrderTerm<3> >
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLSugenoDefuzzifier<OutputTermTuple, LFLLSugenoWeightedAverage> 
        defuzzifier(outputTerms);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);

    scalar ret = defuzzifier.defuzzifyConsequence(inputs, consequence);

    ASSERT_LFLL_REL_EQ(5.738636363636363f, ret);
}


TEST(LFLLSugenoDefuzzifier, TestFirstOrderSum)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLArray<3> inputs = {0.f, 0.4f, 5.f};

    LFLLSugenoFirstOrderTerm<3> o1 = {1.0f, 0.75f, 2.0f, 0.5f};
    LFLLSugenoFirstOrderTerm<3> o2 = {7.0f, 5.0f, 0.25f, 1.0f};


    typedef LFLLTuple<
        LFLLSugenoFirstOrderTerm<3>, 
        LFLLSugenoFirstOrderTerm<3> >
        OutputTermTuple;
    OutputTermTuple outputTerms = makeLFLLTuple(o1, o2);


    LFLLSugenoDefuzzifier<OutputTermTuple, LFLLSugenoWeightedSum> 
        defuzzifier(outputTerms);


    LFLLConsequence<NR> consequence;

    consequence.setTermIndex(0, 1);
    consequence.setVal(0, 0.25f);

    consequence.setTermIndex(1, 2);
    consequence.setVal(1, 0.75f);

    consequence.setTermIndex(2, 2);
    consequence.setVal(2, 0.10f);

    scalar ret = defuzzifier.defuzzifyConsequence(inputs, consequence);

    ASSERT_LFLL_REL_EQ(6.3125f, ret);
}