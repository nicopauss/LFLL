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
#include <lfll/LFLLMinOperator.h>
#include <lfll/LFLLMaxOperator.h>
#include <lfll/LFLLComplementOperator.h>
#include <lfll/LFLLTriangle.h>
#include <lfll/LFLLPiShape.h>
#include <lfll/LFLLInputFuzzifier.h>
#include <lfll/LFLLRulesEngine.h>
#include <lfll/LFLLSugenoDefuzzifier.h>
#include <lfll/LFLLTuple.h>

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

    const LFLLSugenoCrispValues<NbTermsForOutput1> crispValues = {{
        0.0f,  // Output O1
        0.75f, // Output O2
        1.0f   // Output O3
    }};


    typedef LFLLTuple<LFLLTriangle, LFLLTriangle, LFLLPiShape> Input1Types;
    typedef LFLLTuple<LFLLTriangle, LFLLPiShape> Input2Types;

    const Input1Types inputTerms1 = makeLFLLTuple(t1A, t1B, t1C);
    const Input2Types inputTerms2 = makeLFLLTuple(t2X, t2Y);

    const LFLLInputFuzzifier<NbTermsForInput1> inputFuzzifier1(inputTerms1);
    const LFLLInputFuzzifier<NbTermsForInput2> inputFuzzifier2(inputTerms2);
    const LFLLRulesEngine<NbInput, NbRules, NbOutput> rulesEngine(rules);
    const LFLLSugenoDefuzzifier<NbRules, NbTermsForOutput1> defuzzifier(crispValues);
}


scalar ExampleLFLLEngine::process(scalar input1, scalar input2)
{
    // Fuzzify inputs
    const LFLLMembership<NbTermsForInput1> degrees1 =
        inputFuzzifier1.fuzzifyVariable(input1);
    const LFLLMembership<NbTermsForInput2> degrees2 =
        inputFuzzifier2.fuzzifyVariable(input2);

    // Initalise consequences
    LFLLConsequence<NbRules, NbTermsForOutput1> consequence;

    const LFLLMembershipBase* antecedents[NbInput] = {
        &degrees1, &degrees2
    };

    LFLLConsequenceBase* consequences[NbOutput] = {
        &consequence
    };


    // Apply rules
    rulesEngine.applyRules(antecedents, consequences);

    // Defuzzify consequence
    return defuzzifier.defuzzifyConsequence(consequence);
}
