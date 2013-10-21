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
#ifndef LFLLSTATICASSERT_H
#define LFLLSTATICASSERT_H

// Adapted static assert from http://stackoverflow.com/a/1980156

#define LFLL_CONCATENATE(arg1, arg2)   LFLL_CONCATENATE1(arg1, arg2)
#define LFLL_CONCATENATE1(arg1, arg2)  LFLL_CONCATENATE2(arg1, arg2)
#define LFLL_CONCATENATE2(arg1, arg2)  arg1##arg2

#define LFLL_STATIC_ASSERT(expression, message)\
    struct LFLL_CONCATENATE(__static_assertion_at_line_, __LINE__)\
    {\
        detail::LFLLStaticAssert<static_cast<bool>((expression))> LFLL_CONCATENATE(LFLL_CONCATENATE(LFLL_CONCATENATE(STATIC_ASSERTION_FAILED_AT_LINE_, __LINE__), _), message);\
    };\
    typedef detail::LFLLStaticAssertionTest<sizeof(LFLL_CONCATENATE(__static_assertion_at_line_, __LINE__))> LFLL_CONCATENATE(__static_assertion_test_at_line_, __LINE__)

namespace detail {
template<bool> struct LFLLStaticAssert;
template<> struct LFLLStaticAssert<true> {};
template<int i> struct LFLLStaticAssertionTest {};
}

#endif // LFLLSTATICASSERT_H
