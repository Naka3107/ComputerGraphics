#pragma once
#include <iostream>
#include "vec3.h"
#include "vec4.h"

namespace cgmath {
	class mat3 {
	private:

		float n[3][3];

	public:

		mat3();
		mat3(float diagonal);
		mat3(const vec3& a, const vec3& b, const vec3& c);
		mat3(const vec4& a, const vec4& b, const vec4& c);

		vec3& operator[](int column);
		const vec3& operator[](int column) const;
		bool operator==(const mat3& m) const;

		static float determinant(const mat3& m);
		static mat3 inverse(const mat3& m);
		static mat3 transpose(const mat3& m);

		friend inline std::ostream& operator<<(std::ostream& os, const mat3& m) {
			os << m[0][0] << " " << m[1][0] << " " << m[2][0] << "\n" << m[0][1] << " " << m[1][1] << " " << m[2][1] << "\n" << m[0][2] << " " << m[1][2] << " " << m[2][2];
			return os;
		}
	};
	inline vec3 operator*(const mat3& m, const vec3& v) {
		return vec3(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z, m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z, m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
	}
	inline mat3 operator*(const mat3& m1, const mat3& m2) {
		vec3 a(m1[0][0], m1[1][0], m1[2][0]);
		vec3 b(m1[0][1], m1[1][1], m1[2][1]);
		vec3 c(m1[0][2], m1[1][2], m1[2][2]);
		vec3 d(m2[0][0], m2[0][1], m2[0][2]);
		vec3 e(m2[1][0], m2[1][1], m2[1][2]);
		vec3 f(m2[2][0], m2[2][1], m2[2][2]);
		vec3 ad(vec3::dot(a, d), vec3::dot(b, d), vec3::dot(c, d));
		vec3 ae(vec3::dot(a, e), vec3::dot(b, e), vec3::dot(c, e));
		vec3 af(vec3::dot(a, f), vec3::dot(b, f), vec3::dot(c, f));
		mat3 m(ad, ae, af);
		return m;
	}
}