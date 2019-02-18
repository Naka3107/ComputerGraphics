#pragma once
#include <iostream>

namespace cgmath {
	class vec4 {
	public:

		float x;
		float y;
		float z;
		float w;

		vec4();
		vec4(float x, float y, float z, float w);

		float& operator[](int i);
		const float& operator[](int i) const;

		vec4& operator*=(float s);
		vec4& operator/=(float s);
		vec4& operator+=(const vec4& v);
		vec4& operator-=(const vec4& v);

		bool operator==(const vec4& v) const;

		friend inline std::ostream& operator<<(std::ostream& os, const vec4& v) {
			os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
			return os;
		}
	};
	inline vec4 operator*(const vec4& v, float s) {
		return vec4(v.x * s, v.y * s, v.z * s, v.w * s);
	}
	inline vec4 operator*(float s, const vec4& v) {
		return vec4(v.x * s, v.y * s, v.z * s, v.w * s);
	}
	inline vec4 operator/(const vec4& v, float s) {
		return vec4(v.x / s, v.y / s, v.z / s, v.w / s);
	}
	inline vec4 operator+(const vec4& a, const vec4& b) {
		return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}
	inline vec4 operator-(const vec4& a, const vec4& b) {
		return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}
	inline vec4 operator-(const vec4& v) {
		return vec4(-v.x, -v.y, -v.z, -v.w);
	}
}
