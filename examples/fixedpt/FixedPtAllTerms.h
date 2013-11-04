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
#ifndef FIXEDPTALLTERMS_H
#define FIXEDPTALLTERMS_H

#include "FixedPt32.h"

#define LFLL_CUSTOM_SCALAR FixedPt32
#define LFLL_CUSTOM_SCALAR_NAMESPACE fixedpt_math

#include <lfll/LFLL.h>

class FixedPtAllTerms
{
public:
	static void process(
		const LFLL_NAMESPACE_NAME::LFLLArray<1>& inputs,
		LFLL_NAMESPACE_NAME::LFLLArray<1>& outputs);

private:
	FixedPtAllTerms() {}
};

#endif // FIXEDPTALLTERMS_H
