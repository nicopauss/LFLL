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
#ifndef LFLLSUGENOTERMS_H
#define LFLLSUGENOTERMS_H

#include <cassert>

#include <lfll/engine/LFLLDefinitions.h>


LFLL_BEGIN_NAMESPACE

struct LFLLSugenoZeroOrderTerm
{
    scalar value;

    scalar computeTermValue(const scalar[]) const
    {
        return value;
    }
};


template <size_t NI>
struct LFLLSugenoFirstOrderTerm
{
    scalar values[NI+1];

    scalar computeTermValue(const scalar inputs[NI]) const
    {
        scalar result = values[NI];
        for (size_t i = NI ; i > 0 ; )
        {
            --i;
            result += values[i] * inputs[i];
        }
        return result;
    }
};

LFLL_END_NAMESPACE


#endif //LFLLSUGENOTERMS_H
