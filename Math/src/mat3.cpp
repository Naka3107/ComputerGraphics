#include "mat3.h"
#include <math.h>

cgmath::mat3::mat3() : n{0}
{
}

cgmath::mat3::mat3(float diagonal) : n{ {diagonal, 0 , 0}, {0, diagonal, 0}, {0, 0, diagonal} }
{
}

cgmath::mat3::mat3(const vec3& a, const vec3& b, const vec3& c) : n{ {a.x, a.y, a.z}, {b.x, b.y, b.z}, {c.x, c.y, c.z} }
{
}

cgmath::mat3::mat3(const vec4& a, const vec4& b, const vec4& c) : n{ {a.x, a.y, a.z}, {b.x, b.y, b.z}, {c.x, c.y, c.z} }
{
}

cgmath::vec3& cgmath::mat3::operator[](int column)
{
	return *reinterpret_cast<vec3*>(n[column]);
}

const cgmath::vec3& cgmath::mat3::operator[](int column) const
{
	return *reinterpret_cast<const vec3*>(n[column]);
}

bool cgmath::mat3::operator==(const mat3& m) const
{
	bool isEqual = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (n[i][j] != m.n[i][j]) {
				isEqual = false;
			}
		}
	}
	return isEqual;
}

float cgmath::mat3::determinant(const mat3& m)
{
	float det1 = (m.n[1][1] * m.n[2][2] - m.n[2][1] * m.n[1][2]);
	float det2 = (m.n[0][1] * m.n[2][2] - m.n[2][1] * m.n[0][2]);
	float det3 = (m.n[0][1] * m.n[1][2] - m.n[1][1] * m.n[0][2]);
	float det = m.n[0][0] * det1 - m.n[1][0] * det2 + m.n[2][0] * det3;
	return det;
}
cgmath::mat3 cgmath::mat3::inverse(const mat3& m)
{
	int n = 3;
	vec3 a(m.n[0][0], m.n[0][1], m.n[0][2]);
	vec3 b(m.n[1][0], m.n[1][1], m.n[1][2]);
	vec3 c(m.n[2][0], m.n[2][1], m.n[2][2]);
	mat3 m1(a,b,c);
	mat3 m2(1.0f);
	for (int i = 0; i < n; i++) {
		float mul_inv = 1.0f / (m1.n[i][i]);
		for (int j = 0; j < n; j++) {
			m1.n[j][i] *= mul_inv;
			m2.n[j][i] *= mul_inv;
		}
		for (int k = 0; k < n; k++) {
			if (k == i) {
				continue;
			}
			else {
				float negate = -(m1.n[i][k]);
				for (int m = 0; m < n; m++) {
					m1.n[m][k] += m1.n[m][i] * negate;
					m2.n[m][k] += m2.n[m][i] * negate;
				}
			}
		}
	}
	return m2;
}

cgmath::mat3 cgmath::mat3::transpose(const mat3 & m)
{
	vec3 a(m.n[0][0], m.n[1][0], m.n[2][0]);
	vec3 b(m.n[0][1], m.n[1][1], m.n[2][1]);
	vec3 c(m.n[0][2], m.n[1][2], m.n[2][2]);
	mat3 m1(a, b, c);
	return m1;
}

