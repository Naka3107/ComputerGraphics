#include "vec4.h"
#include <math.h>

cgmath::vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

cgmath::vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

float& cgmath::vec4::operator[](int i)
{
	return (&x)[i];
}

const float& cgmath::vec4::operator[](int i) const
{
	return (&x)[i];
}

cgmath::vec4& cgmath::vec4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

cgmath::vec4& cgmath::vec4::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}

cgmath::vec4& cgmath::vec4::operator+=(const vec4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

cgmath::vec4& cgmath::vec4::operator-=(const vec4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

bool cgmath::vec4::operator==(const vec4& v) const
{
	return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
}