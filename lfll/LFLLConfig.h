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
#ifndef LFLLCONFIG_H
#define LFLLCONFIG_H

/************************************************************************/
/*
This file defines some constants used in the fuzzy library.
*/
/************************************************************************/

// Use double instead of float for the scalar type.
// Not really useful and slower.
// #define LFLL_USE_DOUBLE_SCALAR

// Use custom scalar. You can use fixed-precision type.
// #define LFLL_USE_CUSTOM_SCALAR
// typedef custom_scalar scalar

// Use namespace
 #define LFLL_USE_NAMESPACE

// Namespace name if activated
// Default is lfll
// #define LFLL_NAMESPACE_NAME lfll


#endif //LFLLCONFIG_H
