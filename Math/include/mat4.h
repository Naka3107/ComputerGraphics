#pragma once
#include <iostream>
#include "vec4.h"

namespace cgmath {
	class mat4 {
	private:

		float n[4][4];

	public:

		mat4();
		mat4(float diagonal);
		mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d);

		vec4& operator[](int column);
		const vec4& operator[](int column) const;
		bool operator==(const mat4& m) const;

		static mat4 inverse(const mat4& m);

		friend inline std::ostream& operator<<(std::ostream& os, const mat4& m) {
			os << m[0][0] << " " << m[1][0] << " " << m[2][0] << " " << m[3][0] << "\n" << m[0][1] << " " << m[1][1] << " " << m[2][1] << " " << m[3][1] << "\n" << m[0][2] << " " << m[1][2] << " " << m[2][2] << " " << m[3][2] << "\n" << m[0][3] << " " << m[1][3] << " " << m[2][3] << " " << m[3][3];
			return os;
		}
	};
	inline vec4 operator*(const mat4& m, const vec4& v) {
		return vec4(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w, m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w, m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w, m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w);
	}
	inline mat4 operator*(const mat4& m1, const mat4& m2) {
		vec4 a(m1[0][0], m1[1][0], m1[2][0], m1[3][0]);
		vec4 b(m1[0][1], m1[1][1], m1[2][1], m1[3][1]);
		vec4 c(m1[0][2], m1[1][2], m1[2][2], m1[3][2]);
		vec4 d(m1[0][3], m1[1][3], m1[2][3], m1[3][3]);
		vec4 a2(m2[0][0], m2[0][1], m2[0][2], m2[0][3]);
		vec4 b2(m2[1][0], m2[1][1], m2[1][2], m2[1][3]);
		vec4 c2(m2[2][0], m2[2][1], m2[2][2], m2[2][3]);
		vec4 d2(m2[3][0], m2[3][1], m2[3][2], m2[3][3]);
		
		vec4 aa((a.x*a2.x + a.y*a2.y + a.z*a2.z + a.w*a2.w), (b.x*a2.x + b.y*a2.y + b.z*a2.z + b.w*a2.w), (c.x*a2.x + c.y*a2.y + c.z*a2.z + c.w*a2.w), (d.x*a2.x + d.y*a2.y + d.z*a2.z + d.w*a2.w));
		vec4 ab((a.x*b2.x + a.y*b2.y + a.z*b2.z + a.w*b2.w), (b.x*b2.x + b.y*b2.y + b.z*b2.z + b.w*b2.w), (c.x*b2.x + c.y*b2.y + c.z*b2.z + c.w*b2.w), (d.x*b2.x + d.y*b2.y + d.z*b2.z + d.w*b2.w));
		vec4 ac((a.x*c2.x + a.y*c2.y + a.z*c2.z + a.w*c2.w), (b.x*c2.x + b.y*c2.y + b.z*c2.z + b.w*c2.w), (c.x*c2.x + c.y*c2.y + c.z*c2.z + c.w*c2.w), (d.x*c2.x + d.y*c2.y + d.z*c2.z + d.w*c2.w));
		vec4 ad((a.x*d2.x + a.y*d2.y + a.z*d2.z + a.w*d2.w), (b.x*d2.x + b.y*d2.y + b.z*d2.z + b.w*d2.w), (c.x*d2.x + c.y*d2.y + c.z*d2.z + c.w*d2.w), (d.x*d2.x + d.y*d2.y + d.z*d2.z + d.w*d2.w));
		mat4 m(aa, ab, ac, ad);
		return m;
	}
}
