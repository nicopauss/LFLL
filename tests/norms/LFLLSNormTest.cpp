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

TEST_CASE("LFLLSNormTest - Max", "")
{
    LFLLMax sNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == sNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.5f) == sNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.8f) == sNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.5f) == sNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.75f) == sNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLSNormTest - ProbabilisticSum", "")
{
    LFLLProbabilisticSum sNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == sNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.65f) == sNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.82f) == sNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.75f) == sNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.9375f) == sNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLSNormTest - BoundedSum", "")
{
    LFLLBoundedSum sNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == sNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.8f) == sNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.9f) == sNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(1.0f) == sNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(1.0f) == sNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLSNormTest - DrasticSum", "")
{
    LFLLDrasticSum sNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == sNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(1.0f) == sNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(1.0f) == sNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(1.0f) == sNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(1.0f) == sNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLSNormTest - NilpotentMax", "")
{
    LFLLNilpotentMax sNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == sNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.5f) == sNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.8f) == sNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(1.0f) == sNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(1.0f) == sNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLSNormTest - EinsteinSum", "")
{
    LFLLEinsteinSum sNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == sNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.6956521739130436f) == sNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.8333333333333333f) == sNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.8f) == sNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.96f) == sNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLSNormTest - HamacherSum", "")
{
    LFLLHamacherSum sNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == sNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == sNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.5882352941176471f) == sNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.8043478260869565f) == sNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.6666666666666666f) == sNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.8571428571428571f) == sNorm(0.75f, 0.75f));
}