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
#ifndef LFLLARRAY_H
#define LFLLARRAY_H

#include <cassert>
#include <iterator>

#include <lfll/engine/LFLLDefinitions.h>

LFLL_BEGIN_NAMESPACE


/**
* Array with fixed size
*/
template <size_t N>
class LFLLArray
{
public:
    static const size_t staticSize = N;
	
	scalar elements[N];
public:
	typedef scalar         value_type;
    typedef scalar*        iterator;
    typedef const scalar*  const_iterator;
    typedef scalar&        reference;
    typedef const scalar&  const_reference;
    typedef size_t         size_type;
    
	typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    LFLLArray<N>& operator=(const LFLLArray<N>& o)
    {
        std::copy(o.elements, o.elements+N, elements);
        return *this;
    }
    
	size_type size() const
	{
		return N;
	}
	
	reference operator[](size_t i)
	{
		assert(i < N);
		return elements[i];
	}
	
	value_type operator[](size_t i) const
	{
		assert(i < N);
		return elements[i];
	}
	
	
	iterator        begin()       { return elements; }
    const_iterator  begin() const { return elements; }
    const_iterator cbegin() const { return elements; }
    
    iterator        end()       { return elements+N; }
    const_iterator  end() const { return elements+N; }
    const_iterator cend() const { return elements+N; }
    
    reverse_iterator		rbegin() 		{ return reverse_iterator(end()); }
    const_reverse_iterator	rbegin()  const { return const_reverse_iterator(end()); }
    const_reverse_iterator	crbegin() const { return const_reverse_iterator(end()); }
    
    reverse_iterator		rend() 		  { return reverse_iterator(begin()); }
    const_reverse_iterator	rend()  const { return const_reverse_iterator(begin()); }
    const_reverse_iterator	crend() const { return const_reverse_iterator(begin()); }
    
    // front() and back()
    reference  front() 		 { return elements[0]; }
    value_type front() const { return elements[0]; }
    
    reference  back() 		{ return elements[N-1]; }
    value_type back() const { return elements[N-1]; }
	
	const scalar* data() const { return elements; }
    scalar* data() { return elements; }
	
};

LFLL_END_NAMESPACE

#endif //LFLLARRAY_H
