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

TEST_CASE("LFLLTNormTest - Min", "")
{
    LFLLMin tNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == tNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.3f) == tNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.1f) == tNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.5f) == tNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.75f) == tNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLTNormTest - ProbabilisticProduct", "")
{
    LFLLProbabilisticProduct tNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == tNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.15f) == tNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.08f) == tNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.25f) == tNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.5625f) == tNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLTNorm - BoundedDifference", "")
{
    LFLLBoundedDifference tNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == tNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.5f) == tNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLTNorm - DrasticProduct", "")
{
    LFLLDrasticProduct tNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == tNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLTNorm - NilpotentMin", "")
{
    LFLLNilpotentMin tNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == tNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.0f) == tNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.75f) == tNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLTNorm - EinsteinProduct", "")
{
    LFLLEinsteinProduct tNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == tNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.11111111111111111f) == tNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.06779661016949154f) == tNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.2f) == tNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.5294117647058824f) == tNorm(0.75f, 0.75f));
}


TEST_CASE("LFLLTNorm - HamacherProduct", "")
{
    LFLLHamacherProduct tNorm;

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ZERO_SCALAR));
    REQUIRE(LFLL_APPROX(ONE_SCALAR) == tNorm(ONE_SCALAR, ONE_SCALAR));

    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ZERO_SCALAR, ONE_SCALAR));
    REQUIRE(LFLL_APPROX(ZERO_SCALAR) == tNorm(ONE_SCALAR, ZERO_SCALAR));

    REQUIRE(LFLL_APPROX(0.23076923076923075f) == tNorm(0.5f, 0.3f));
    REQUIRE(LFLL_APPROX(0.09756097560975611f) == tNorm(0.1f, 0.8f));
    REQUIRE(LFLL_APPROX(0.3333333333333333f) == tNorm(0.5f, 0.5f));
    REQUIRE(LFLL_APPROX(0.6f) == tNorm(0.75f, 0.75f));
}