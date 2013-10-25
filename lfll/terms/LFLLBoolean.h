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
#ifndef LFLLBOOLEAN_H
#define LFLLBOOLEAN_H

#include <lfll/engine/LFLLDefinitions.h>

LFLL_BEGIN_NAMESPACE


/**
  * Boolean term.
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     0, & x < 0.5 \\
     1, & x \geq 0.5 \\
   \end{array}
\right \}
  * @f]
  */
class LFLLBoolean
{
public:
    LFLLBoolean(bool val)
        : m_boolVal(val)
    {}

    inline dom membership(scalar val) const
    {
        return ((val >= HALF_SCALAR) == m_boolVal) ? MAX_DOM : MIN_DOM;
    }

private:
    bool m_boolVal;
};

LFLL_END_NAMESPACE

#endif //LFLLBOOLEAN_H
