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
#ifndef LFLLSINGLETON_H
#define LFLLSINGLETON_H

#include <lfll/LFLLDefinitions.h>
#include <lfll/LFLLMath.h>

LFLL_BEGIN_NAMESPACE

/**
  * Singleton Term
  *
  * @f[
\renewcommand{\arraystretch}{2.25}
x:R \rightarrow  f(x) = \left \{
   \begin{array}{cc}
     1, & x = val \\
     0, & x \neq val \\
   \end{array}
\right \}
  * @f]
  */
class LFLLSingleton
{
public:

    LFLLSingleton(scalar val)
        : m_val(val)
    {}

    inline dom membership(scalar val) const
    {
        if (math::isEqualTo(val, m_val)) {
            return MAX_DOM;
        }
        return MIN_DOM;
    }
protected:
    scalar m_val;
};

LFLL_END_NAMESPACE


#endif //LFLLSINGLETON_H
