#include "vec3.h"
#include <math.h>

cgmath::vec3::vec3() : x(0.0f), y(0.0f), z(0.0f)
{
}

cgmath::vec3::vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

float& cgmath::vec3::operator[](int i)
{
	return (&x)[i];
}

const float& cgmath::vec3::operator[](int i) const
{
	return (&x)[i];
}

cgmath::vec3& cgmath::vec3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

cgmath::vec3& cgmath::vec3::operator*=(const vec4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

cgmath::vec3& cgmath::vec3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

cgmath::vec3& cgmath::vec3::operator+=(const vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

cgmath::vec3& cgmath::vec3::operator-=(const vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

bool cgmath::vec3::operator==(const vec3& v) const
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}

float cgmath::vec3::magnitude() const
{
	return sqrt(x*x + y*y + z*z);
}

float cgmath::vec3::magnitudeNoSqrt() const
{
	return (x*x + y * y + z * z);
}

void cgmath::vec3::normalize()
{
	float m = magnitude();
	x /= m;
	y /= m;
	z /= m;
}

float cgmath::vec3::magnitude(const vec3& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

cgmath::vec3 cgmath::vec3::normalize(const vec3& v)
{
	float m = magnitude(v);
	vec3 vf;
	vf[0] = v.x / m;
	vf[1] = v.y / m;
	vf[2] = v.z / m;
	return vf;
}

float cgmath::vec3::dot(const vec3& a, const vec3& b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

cgmath::vec3 cgmath::vec3::cross(const vec3 & a, const vec3 & b)
{
	vec3 vf;
	vf[0] = (a.y*b.z - a.z*b.y);
	vf[1] = (a.z*b.x - a.x*b.z);
	vf[2] = (a.x*b.y - a.y*b.x);
	return vf;
}


