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

using namespace lfll_math;

TEST_CASE("LFLLMathTest - Srel", "")
{
    REQUIRE(42.f == srel(0.42f, 0.f, 100.f));
    REQUIRE(75.f == srel(0.5f, 50.f, 100.f));
}

TEST_CASE("LFLLMathTest - IsLessThan", "")
{
    REQUIRE_FALSE(isLessThan(0.5f, 0.5f));
    REQUIRE_FALSE(isLessThan(0.501f, 0.5f));
    REQUIRE_FALSE(isLessThan(0.49999999f, 0.5f));
    REQUIRE(isLessThan(0.499f, 0.5f));
}


TEST_CASE("LFLLMathTest - IsGreaterThan", "")
{
    REQUIRE_FALSE(isGreaterThan(0.5f, 0.5f));
    REQUIRE_FALSE(isGreaterThan(0.499f, 0.5f));
    REQUIRE_FALSE(isGreaterThan(0.50000001f, 0.5f));
    REQUIRE(isGreaterThan(0.501f, 0.5f));
}


TEST_CASE("LFLLMathTest - IsEqualTo", "")
{
    REQUIRE(isEqualTo(0.50000001f, 0.5f));
    REQUIRE(isEqualTo(0.5f, 0.5f));
    REQUIRE(isEqualTo(0.49999999f, 0.5f));
    REQUIRE_FALSE(isEqualTo(0.499f, 0.5f));
    REQUIRE_FALSE(isEqualTo(0.501f, 0.5f));
}

TEST_CASE("LFLLMathTest - IsLessOrEqualTo", "")
{
    REQUIRE(isLessOrEqualTo(0.5f, 0.5f));
    REQUIRE(isLessOrEqualTo(0.499f, 0.5f));
    REQUIRE(isLessOrEqualTo(0.49999999f, 0.5f));
    REQUIRE(isLessOrEqualTo(0.50000001f, 0.5f));
    REQUIRE_FALSE(isLessOrEqualTo(0.501f, 0.5f));
}

TEST_CASE("LFLLMathTest - IsGreaterOrEqualTo", "")
{
    REQUIRE(isGreaterOrEqualTo(0.5f, 0.5f));
    REQUIRE(isGreaterOrEqualTo(0.501f, 0.5f));
    REQUIRE(isGreaterOrEqualTo(0.49999999f, 0.5f));
    REQUIRE(isGreaterOrEqualTo(0.50000001f, 0.5f));
    REQUIRE_FALSE(isGreaterOrEqualTo(0.499f, 0.5f));
}

TEST_CASE("LFLLMathTest - Max", "")
{
    REQUIRE(0.4f == max(0.4f, 0.2f));
    REQUIRE(0.8f == max(0.8f, 0.1f));
}

TEST_CASE("LFLLMathTest - Min", "")
{
    REQUIRE(0.2f == min(0.4f, 0.2f));
    REQUIRE(0.1f == min(0.8f, 0.1f));
}

