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

TEST_CASE("LFLLAccumulated - TestMax", "")
{
    LFLLBell bell(0.4f, 3.0f, 0.0f);
    LFLLGaussian gaussian(0.3f, 0.0f);
    LFLLPiShape piShape(-1.0f, -0.05f, 0.1f, 1.0f);

    typedef LFLLTuple<LFLLBell, LFLLGaussian, LFLLPiShape> TermTuple;
    TermTuple terms = makeLFLLTuple(bell, gaussian, piShape);

    LFLLAccumulated<TermTuple, LFLLMax> term(terms);


    REQUIRE(LFLL_APPROX(0.0004f) == term.membership(-1.5f));
    REQUIRE(LFLL_APPROX(0.0041f) == term.membership(-1.0f));
    REQUIRE(LFLL_APPROX(0.7285f) == term.membership(-0.4f));
    REQUIRE(LFLL_APPROX(1.0f) == term.membership(0.0f));
    REQUIRE(LFLL_APPROX(0.9846f) == term.membership(0.2f));
    REQUIRE(LFLL_APPROX(0.0988f) == term.membership(0.8f));
    REQUIRE(LFLL_APPROX(0.0041f) == term.membership(1.0f));
    REQUIRE(LFLL_APPROX(0.0005f) == term.membership(1.4f));
}

TEST_CASE("LFLLAccumulated - TestBoundedSum", "")
{
    LFLLBell bell(0.4f, 3.0f, 0.0f);
    LFLLGaussian gaussian(0.3f, 0.0f);
    LFLLPiShape piShape(-1.0f, -0.05f, 0.1f, 1.0f);

    typedef LFLLTuple<LFLLBell, LFLLGaussian, LFLLPiShape> TermTuple;
    TermTuple terms = makeLFLLTuple(bell, gaussian, piShape);

    LFLLAccumulated<TermTuple, LFLLBoundedSum> term(terms);


    REQUIRE(LFLL_APPROX(0.0004f) == term.membership(-1.5f));
    REQUIRE(LFLL_APPROX(0.0080f) == term.membership(-1.0f));
    REQUIRE(LFLL_APPROX(1.0f) == term.membership(-0.4f));
    REQUIRE(LFLL_APPROX(1.0f) == term.membership(0.0f));
    REQUIRE(LFLL_APPROX(1.0f) == term.membership(0.2f));
    REQUIRE(LFLL_APPROX(0.1428f) == term.membership(0.8f));
    REQUIRE(LFLL_APPROX(0.0080f) == term.membership(1.0f));
    REQUIRE(LFLL_APPROX(0.0005f) == term.membership(1.4f));
}

