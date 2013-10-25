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
#include "ExampleLFLLEngine.h"

// Unnamed namespace
namespace {
    const size_t NbInput = 2;
    const size_t NbTermsForInput1 = 3;
    const size_t NbTermsForInput2 = 2;
    const size_t NbRules = 5;
    const size_t NbOutput = 1;
    const size_t NbTermsForOutput1 = 3;

    const LFLLTriangle t1A(-0.4f, 0.0f, 0.3f);
    const LFLLTriangle t1B(0.05f, 0.3f, 0.9f);
    const LFLLPiShape t1C(0.1f, 1.0f, 1.2f, 1.4f);

    const LFLLTriangle t2X(-0.4f, 0.0f, 0.6f);
    const LFLLPiShape  t2Y(0.0f, 0.2f, 0.6f, 1.0f);

    const LFLLSugenoZeroOrderTerm o1 = {0.0f};
    const LFLLSugenoZeroOrderTerm o2 = {0.75f};
    const LFLLSugenoZeroOrderTerm o3 = {1.0f};

    const LFLLRules<NbInput, NbRules, NbOutput> rules = {{
        // If A and X then O1 with 1.0
        {{1, 1}, {1}, 1.f, false},

        // If B and X then O1 with 0.5
        {{2, 1}, {1}, .5f, false},

        // If C then O2 with 0.5
        {{3, 0}, {2}, .5f, false},

        // If A or Y then O1 with 1.0
        {{1, 2}, {1}, 1.f, true},

        // If B and Y then O2 with 0.5
        {{2, 2}, {2}, .5, false}
    }};


    typedef LFLLTuple<const LFLLTriangle, const LFLLTriangle, const LFLLPiShape> Input1Types;
    typedef LFLLTuple<const LFLLTriangle, const LFLLPiShape> Input2Types;

    const Input1Types inputTerms1 = makeLFLLTuple(t1A, t1B, t1C);
    const Input2Types inputTerms2 = makeLFLLTuple(t2X, t2Y);

    typedef LFLLTuple<
            const LFLLSugenoZeroOrderTerm,
            const LFLLSugenoZeroOrderTerm,
            const LFLLSugenoZeroOrderTerm> OutputTermTuple;

    const OutputTermTuple outputTerms = makeLFLLTuple(o1, o2, o3);


    const LFLLInputFuzzifier<Input1Types> inputFuzzifier1(inputTerms1);
    const LFLLInputFuzzifier<Input2Types> inputFuzzifier2(inputTerms2);
    const LFLLRulesEngine<NbInput, NbRules, NbOutput> rulesEngine(rules);
    const LFLLSugenoDefuzzifier<OutputTermTuple> defuzzifier(outputTerms);
}


scalar ExampleLFLLEngine::process(const scalar inputs[])
{
    // Fuzzify inputs
    const LFLLMembership<NbTermsForInput1> degrees1 =
            inputFuzzifier1.fuzzifyVariable(inputs[0]);
    const LFLLMembership<NbTermsForInput2> degrees2 =
            inputFuzzifier2.fuzzifyVariable(inputs[1]);

    // Initalise consequences
    LFLLConsequence<NbRules, NbTermsForOutput1> consequence;

    // Tuples initialisation
    typedef LFLLTuple<
            const LFLLMembership<NbTermsForInput1>,
            const LFLLMembership<NbTermsForInput2> >
            AntecedentTuple;

    typedef LFLLTuple<
            LFLLConsequence<NbRules, NbTermsForOutput1> >
            ConsequenceTuple;

    const AntecedentTuple antecedents =
            makeLFLLTuple(degrees1, degrees2);
    ConsequenceTuple consequences =
            makeLFLLTuple(consequence);


    // Apply rules
    rulesEngine.applyRules(antecedents, consequences);

    // Defuzzify consequence
    return defuzzifier.defuzzifyConsequence(inputs, consequence);
}
