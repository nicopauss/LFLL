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
#ifndef FIXEDPT32_H
#define FIXEDPT32_H

#include <stdint.h>

#include <iostream>
#include <string>


extern "C" {
#include "fixedptc.h"
}

class FixedPt32;

namespace fixedpt_math {
	FixedPt32 abs(const FixedPt32& p);
	FixedPt32 sqrt(const FixedPt32& p);
	FixedPt32 sin(const FixedPt32& p);
	FixedPt32 cos(const FixedPt32& p);
	FixedPt32 tan(const FixedPt32& p);
	FixedPt32 exp(const FixedPt32& p);
	FixedPt32 log(const FixedPt32& p);
	FixedPt32 pow(const FixedPt32& p, const FixedPt32& exp);
}

// Define a fixed point 32 bit 16.16 numeric
class FixedPt32
{
public:
	FixedPt32() : m_val(0) {}
	FixedPt32(const FixedPt32 &o) : m_val(o.m_val) {}
	FixedPt32(const float val) : m_val(fixedpt_rconst(val)) {}
	FixedPt32(const double val) : m_val(fixedpt_rconst(val)) {}
	FixedPt32(const int32_t val) : m_val(fixedpt_fromint(val)) {}
	FixedPt32(const uint32_t val) : m_val(fixedpt_fromint(val)) {}

	FixedPt32& operator=(const FixedPt32 &o) { m_val = o.m_val; return *this; }
	
	
	FixedPt32 operator+() const { return fromFixedpt(+m_val); }
	FixedPt32 operator-() const { return fromFixedpt(-m_val); }
	
	FixedPt32& operator+=(const FixedPt32 &o) { m_val = fixedpt_add(m_val, o.m_val); return *this; }
	FixedPt32& operator-=(const FixedPt32 &o) { m_val = fixedpt_sub(m_val, o.m_val); return *this; }
	FixedPt32& operator*=(const FixedPt32 &o) { m_val = fixedpt_mul(m_val, o.m_val); return *this; }
	FixedPt32& operator/=(const FixedPt32 &o) { m_val = fixedpt_div(m_val, o.m_val); return *this; }

	FixedPt32 operator+(const FixedPt32 &o) const { return fromFixedpt(fixedpt_add(m_val, o.m_val)); }
	FixedPt32 operator-(const FixedPt32 &o) const { return fromFixedpt(fixedpt_sub(m_val, o.m_val)); }
	FixedPt32 operator*(const FixedPt32 &o) const { return fromFixedpt(fixedpt_mul(m_val, o.m_val)); }
	FixedPt32 operator/(const FixedPt32 &o) const { return fromFixedpt(fixedpt_div(m_val, o.m_val)); }
	
	bool operator==(const FixedPt32 &o) const { return m_val == o.m_val; }
	bool operator!=(const FixedPt32 &o) const { return m_val != o.m_val; }
	bool operator<(const FixedPt32 &o) const { return m_val < o.m_val; }
	bool operator>(const FixedPt32 &o) const { return m_val > o.m_val; }
	bool operator<=(const FixedPt32 &o) const { return m_val <= o.m_val; }
	bool operator>=(const FixedPt32 &o) const { return m_val >= o.m_val; }
	
	int32_t toInt() const { return fixedpt_toint(m_val); }
	std::string toString() const
	{
		char str[50];
		fixedpt_str(m_val, str, -2);
		return std::string(str);
	}
	
private:
	FixedPt32(const fixedpt val, bool) : m_val(val) {}
	static FixedPt32 fromFixedpt(fixedpt val) { return FixedPt32(val, true); }
	
	friend std::ostream& operator<<(std::ostream &os, const FixedPt32& p);
	friend FixedPt32 fixedpt_math::abs(const FixedPt32& p);
	friend FixedPt32 fixedpt_math::sqrt(const FixedPt32& p);
	friend FixedPt32 fixedpt_math::sin(const FixedPt32& p);
	friend FixedPt32 fixedpt_math::cos(const FixedPt32& p);
	friend FixedPt32 fixedpt_math::tan(const FixedPt32& p);
	friend FixedPt32 fixedpt_math::exp(const FixedPt32& p);
	friend FixedPt32 fixedpt_math::log(const FixedPt32& p);
	friend FixedPt32 fixedpt_math::pow(const FixedPt32& p, const FixedPt32& exp);
	
private:
	fixedpt m_val;
};

inline std::ostream& operator<<(std::ostream &os, const FixedPt32& p)
{
    return os << p.toString();
}


namespace fixedpt_math {
	inline FixedPt32 abs(const FixedPt32& p)
	{
		return FixedPt32::fromFixedpt(fixedpt_abs(p.m_val));
	}
	
	inline FixedPt32 sqrt(const FixedPt32& p)
	{
		return FixedPt32::fromFixedpt(fixedpt_sqrt(p.m_val));
	}
	
	inline FixedPt32 sin(const FixedPt32& p)
	{
		return FixedPt32::fromFixedpt(fixedpt_sin(p.m_val));
	}
	
	inline FixedPt32 cos(const FixedPt32& p)
	{
		return FixedPt32::fromFixedpt(fixedpt_cos(p.m_val));
	}
	
	inline FixedPt32 tan(const FixedPt32& p)
	{
		return FixedPt32::fromFixedpt(fixedpt_tan(p.m_val));
	}
	
	inline FixedPt32 exp(const FixedPt32& p)
	{
		return FixedPt32::fromFixedpt(fixedpt_exp(p.m_val));
	}
	
	inline FixedPt32 log(const FixedPt32& p)
	{
		return FixedPt32::fromFixedpt(fixedpt_ln(p.m_val));
	}
	
	inline FixedPt32 pow(const FixedPt32& p, const FixedPt32& exp)
	{
		return FixedPt32::fromFixedpt(fixedpt_pow(p.m_val, exp.m_val));
	}
}


#endif // FIXEDPT32_H
