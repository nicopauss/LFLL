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

TEST_CASE("LFLLSigmoidProduct - Test", "")
{
    LFLLSigmoidProduct term(
        8.14f, -0.336f, -8.82f, 0.421f);

    REQUIRE(LFLL_APPROX(0.0001f) == term.membership(-1.5f));
    REQUIRE(LFLL_APPROX(0.0045f) == term.membership(-1.0f));
    REQUIRE(LFLL_APPROX(0.3724f) == term.membership(-0.4f));
    REQUIRE(LFLL_APPROX(0.9167f) == term.membership(0.0f));
    REQUIRE(LFLL_APPROX(0.8644f) == term.membership(0.2f));
    REQUIRE(LFLL_APPROX(0.0341f) == term.membership(0.8f));
    REQUIRE(LFLL_APPROX(0.0060f) == term.membership(1.0f));
    REQUIRE(LFLL_APPROX(0.0002f) == term.membership(1.4f));
}
