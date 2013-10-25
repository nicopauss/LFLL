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

TEST(LFLLRulesEngineTest, Test)
{
    const size_t NI = 2;
    const size_t NR = 3;
    const size_t NO = 2;

    // Initialisation

    const LFLLRules<NI, NR, NO> rules = {{
        // Rule 1
        {
            {1, 2}, {1, 0}, 1.f, false
        },

        // Rule 2
        {
            {-2, 1}, {2, 1}, 1.f, false
        },

        //Rule 3
        {
            {3, 2}, {0, -1}, .5f, true
        }
    }};

    LFLLMembership<3> degrees1;
    LFLLMembership<2> degrees2;
    LFLLConsequence<NR, 2> consequence1;
    LFLLConsequence<NR, 2> consequence2;

    typedef LFLLTuple<
            LFLLMembership<3>,
            LFLLMembership<2> >
            AntecedentTuple;

    typedef LFLLTuple<
            LFLLConsequence<NR, 2>,
            LFLLConsequence<NR, 2> >
            ConsequenceTuple;

    const AntecedentTuple antecedents =
            makeLFLLTuple(degrees1, degrees2);
    ConsequenceTuple consequences =
            makeLFLLTuple(consequence1, consequence2);

    degrees1[0] = scalarToDom(0.48f);
    degrees1[1] = scalarToDom(0.09f);
    degrees1[2] = scalarToDom(0.f);

    degrees2[0] = scalarToDom(0.56f);
    degrees2[1] = scalarToDom(0.16f);

    const LFLLRulesEngine<NI, NR, NO,
        LFLLMin, LFLLMax, LFLLNot>
        fTr(rules);

    fTr.applyRules(antecedents, consequences);


    dom valPart = DOM_DIFF - (dom)(degrees2[1]/2.f + 0.5f);

    ASSERT_EQ(scalarToDom(0.16f), consequence1.getVal(0, 0));
    ASSERT_EQ(scalarToDom(0.f), consequence1.getVal(0, 1));
    ASSERT_EQ(scalarToDom(0.f), consequence1.getVal(0, 2));

    ASSERT_EQ(scalarToDom(0.f), consequence1.getVal(1, 0));
    ASSERT_EQ(scalarToDom(0.56f), consequence1.getVal(1, 1));
    ASSERT_EQ(scalarToDom(0.f), consequence1.getVal(1, 2));

    ASSERT_EQ(scalarToDom(0.f), consequence2.getVal(0, 0));
    ASSERT_EQ(scalarToDom(0.56f), consequence2.getVal(0, 1));
    ASSERT_EQ(valPart, consequence2.getVal(0, 2));

    ASSERT_EQ(scalarToDom(0.f), consequence2.getVal(1, 0));
    ASSERT_EQ(scalarToDom(0.f), consequence2.getVal(1, 1));
    ASSERT_EQ(scalarToDom(0.f), consequence2.getVal(1, 2));
}
