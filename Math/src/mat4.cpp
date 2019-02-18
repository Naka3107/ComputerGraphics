#include "mat4.h"
#include <math.h>

cgmath::mat4::mat4() : n{ 0 }
{
}

cgmath::mat4::mat4(float diagonal) : n{ {diagonal, 0 , 0, 0}, {0, diagonal, 0, 0}, {0, 0, diagonal, 0}, {0, 0, 0, diagonal} }
{
}

cgmath::mat4::mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d) : n{ {a.x, a.y, a.z, a.w}, {b.x, b.y, b.z, b.w}, {c.x, c.y, c.z, c.w}, {d.x, d.y, d.z, d.w} }
{
}

cgmath::vec4& cgmath::mat4::operator[](int column)
{
	return reinterpret_cast<vec4&>(n[column]);
}

const cgmath::vec4& cgmath::mat4::operator[](int column) const
{
	return reinterpret_cast<const vec4&>(n[column]);
}

bool cgmath::mat4::operator==(const mat4& m) const
{
	bool isEqual = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (n[i][j] != m.n[i][j]) {
				isEqual = false;
			}
		}
	}
	return isEqual;
}

cgmath::mat4 cgmath::mat4::inverse(const mat4& m)
{
	int n = 4;
	vec4 a(m.n[0][0], m.n[0][1], m.n[0][2], m.n[0][3]);
	vec4 b(m.n[1][0], m.n[1][1], m.n[1][2], m.n[1][3]);
	vec4 c(m.n[2][0], m.n[2][1], m.n[2][2], m.n[2][3]);
	vec4 d(m.n[3][0], m.n[3][1], m.n[3][2], m.n[3][3]);
	mat4 m1(a, b, c, d);
	mat4 m2(1.0f);
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
