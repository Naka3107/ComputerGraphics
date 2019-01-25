#include "stdafx.h"
#include "CppUnitTest.h"

//#include <cmath>
//#include <limits>
//#include <locale>
//#include <codecvt>
//
//#include "vec3.h"
//#include "mat3.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace Microsoft
//{
//	namespace VisualStudio
//	{
//		namespace CppUnitTestFramework
//		{
//			template<>
//			static std::wstring ToString<cgmath::vec3>(const cgmath::vec3& v)
//			{
//				return L"(" + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L", " + std::to_wstring(v.z) + L")";
//			}
//
//			template<>
//			static std::wstring ToString<cgmath::mat3>(const cgmath::mat3& m)
//			{
//				std::stringstream ss;
//				ss << m;
//				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//				std::wstring wide = converter.from_bytes(ss.rdbuf()->str());
//				return wide;
//			}
//		}
//	}
//}
//
//namespace MathTest
//{
//	TEST_CLASS(mat3_test)
//	{
//	public:
//		TEST_METHOD(ConstructorTest)
//		{
//			cgmath::mat3 a;
//			Assert::AreEqual(0.0f, a[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[2][2], std::numeric_limits<float>::epsilon());
//
//			cgmath::mat3 b(1.0f);
//			Assert::AreEqual(1.0f, b[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, b[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, b[2][2], std::numeric_limits<float>::epsilon());
//
//			cgmath::mat3 c(-7.0f);
//			Assert::AreEqual(-7.0f, c[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, c[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, c[2][2], std::numeric_limits<float>::epsilon());
//
//			cgmath::vec3 col1(0.0f, 1.0f, 2.0f);
//			cgmath::vec3 col2(3.0f, 4.0f, 5.0f);
//			cgmath::vec3 col3(6.0f, 7.0f, 8.0f);
//			cgmath::mat3 d(col1, col2, col3);
//			Assert::AreEqual(0.0f, d[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, d[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, d[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, d[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(4.0f, d[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f, d[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(6.0f, d[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(7.0f, d[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(8.0f, d[2][2], std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(IndexTest)
//		{
//			cgmath::vec3 col1(1.0f, 2.0f, 3.0f);
//			cgmath::vec3 col2(4.0f, 5.0f, 6.0f);
//			cgmath::vec3 col3(7.0f, 8.0f, 9.0f);
//			cgmath::mat3 a(col1, col2, col3);
//			Assert::AreEqual(1.0f, a[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, a[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, a[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(4.0f, a[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f, a[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(6.0f, a[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(7.0f, a[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(8.0f, a[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(9.0f, a[2][2], std::numeric_limits<float>::epsilon());
//
//			a[0][0] = 1.0f + 22.0f;
//			a[0][1] = 22.0f - 3.0f;
//			a[0][2] = 18.0f;
//			a[1][0] -= 2.0f;
//			a[1][1] += 11.0f;
//			a[1][2] = 6.0f / 3.0f;
//			a[2][0] = 7.0f * 3.0f;
//			a[2][1] *= 2.0f;
//			a[2][2] /= 3.0f;
//
//			Assert::AreEqual(1.0f + 22.0f, a[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(22.0f - 3.0f, a[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(18.0f, a[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(4.0f - 2.0f, a[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f + 11.0f, a[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(6.0f / 3.0f, a[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(7.0f * 3.0f, a[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(8.0f * 2.0f, a[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(9.0f / 3.0f, a[2][2], std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(EqualityTest)
//		{
//			cgmath::mat3 a;
//			cgmath::mat3 b;
//			Assert::IsTrue(a == b);
//
//			cgmath::vec3 col1(1.0f, 2.0f, 3.0f);
//			cgmath::vec3 col2(4.0f, 5.0f, 6.0f);
//			cgmath::vec3 col3(7.0f, 8.0f, 9.0f);
//			cgmath::mat3 c(col1, col2, col3);
//			Assert::IsTrue(a == b);
//			Assert::IsFalse(a == c);
//			Assert::IsFalse(b == c);
//
//			cgmath::mat3 d(-col1, col2, -col3);
//			Assert::IsTrue(a == b);
//			Assert::IsFalse(a == c);
//			Assert::IsFalse(a == d);
//			Assert::IsFalse(b == c);
//			Assert::IsFalse(b == d);
//			Assert::IsFalse(c == d);
//
//			cgmath::mat3 e;
//			e[0] = col1;
//			e[1] = col2;
//			e[2] = col3;
//			Assert::IsTrue(a == b);
//			Assert::IsFalse(a == c);
//			Assert::IsFalse(a == d);
//			Assert::IsFalse(a == e);
//			Assert::IsFalse(b == c);
//			Assert::IsFalse(b == d);
//			Assert::IsFalse(b == e);
//			Assert::IsFalse(c == d);
//			Assert::IsTrue(c == e);
//			Assert::IsFalse(d == e);
//		}
//
//		TEST_METHOD(DeterminantTest)
//		{
//			cgmath::mat3 a;
//			Assert::AreEqual(0.0f, cgmath::mat3::determinant(a), std::numeric_limits<float>::epsilon());
//
//			cgmath::mat3 b(3.0f);
//			Assert::AreEqual(27.0f, cgmath::mat3::determinant(b), std::numeric_limits<float>::epsilon());
//
//			cgmath::vec3 c1(1.0f, -4.0f, 7.0f);
//			cgmath::vec3 c2(2.0f, 5.0f, 8.0f);
//			cgmath::vec3 c3(-3.0f, 6.0f, 9.0f);
//			cgmath::mat3 c(c1, c2, c3);
//			Assert::AreEqual(354.0f, cgmath::mat3::determinant(c), std::numeric_limits<float>::epsilon());
//
//			cgmath::vec3 d1(2.0f, 2.0f, 2.0f);
//			cgmath::mat3 d(d1, d1, d1);
//			Assert::AreEqual(0.0f, cgmath::mat3::determinant(d), std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(Inverse)
//		{
//			cgmath::mat3 a;
//			for (auto& i : { 0, 1, 2 })
//				for (auto& j : { 0, 1, 2 })
//					Assert::IsTrue(std::isnan(cgmath::mat3::inverse(a)[i][j]));
//
//			cgmath::mat3 b(1.0f);
//			Assert::AreEqual<cgmath::mat3>(b, cgmath::mat3::inverse(b));
//
//			cgmath::mat3 c(2.0f);
//			cgmath::mat3 d(0.5f);
//			Assert::AreEqual<cgmath::mat3>(d, cgmath::mat3::inverse(c));
//
//			cgmath::vec3 e1(1.0f, 4.0f, -7.0f);
//			cgmath::vec3 e2(2.0f, -5.0f, 8.0f);
//			cgmath::vec3 e3(3.0f, 6.0f, 9.0f);
//			cgmath::mat3 e(e1, e2, e3);
//			cgmath::mat3 f = cgmath::mat3::inverse(e);
//			Assert::AreEqual(31.0f / 86.0f, f[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(13.0f / 43.0f, f[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f / 86.0f, f[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-1.0f / 43.0f, f[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-5.0f / 43.0f, f[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(11.0f / 129.0f, f[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-9.0f / 86.0f, f[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-1.0f / 43.0f, f[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(13.0f / 258.0f, f[2][2], std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(Transpose)
//		{
//			cgmath::mat3 a;
//			cgmath::mat3 b = cgmath::mat3::transpose(a);
//			for (auto& i : { 0, 1, 2 })
//				for (auto& j : { 0, 1, 2 })
//					Assert::AreEqual(0.0f, b[i][j], std::numeric_limits<float>::epsilon());
//
//			cgmath::mat3 c(1.0f);
//			Assert::AreEqual<cgmath::mat3>(c, cgmath::mat3::transpose(c));
//
//			cgmath::vec3 d1(1.0f, 2.0f, 3.0f);
//			cgmath::vec3 d2(-4.0f, -5.0f, -6.0f);
//			cgmath::vec3 d3(7.0f, 8.0f, 9.0f);
//			cgmath::mat3 d(d1, d2, d3);
//			cgmath::mat3 e = cgmath::mat3::transpose(d);
//			Assert::AreEqual(1.0f, e[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-4.0f, e[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(7.0f, e[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, e[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-5.0f, e[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(8.0f, e[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, e[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-6.0f, e[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(9.0f, e[2][2], std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(StreamExtraction)
//		{
//			std::stringstream ss1;
//			cgmath::mat3 a;
//			ss1 << a;
//			std::string matstring1 = ss1.rdbuf()->str();
//			Assert::AreEqual<std::string>("0 0 0\n0 0 0\n0 0 0", matstring1);
//
//			std::stringstream ss2;
//			cgmath::vec3 col1(1.0f, 2.0f, 3.0f);
//			cgmath::vec3 col2(4.0f, 5.0f, 6.0f);
//			cgmath::vec3 col3(7.0f, 8.0f, 9.0f);
//			cgmath::mat3 b(col1, col2, col3);
//			ss2 << b;
//			std::string vecstring2 = ss2.rdbuf()->str();
//			Assert::AreEqual<std::string>("1 4 7\n2 5 8\n3 6 9", vecstring2);
//		}
//
//		TEST_METHOD(Mat3xVec3)
//		{
//			cgmath::vec3 v1(3.0f, 6.0f, 4.0f);
//			cgmath::mat3 m(1.0f);
//			Assert::AreEqual<cgmath::vec3>(v1, m * v1);
//
//			m[0][0] *= 3.0f;
//			m[1][1] *= 3.0f;
//			m[2][2] *= 3.0f;
//			Assert::AreEqual<cgmath::vec3>(v1 * 3.0f, m * v1);
//
//			cgmath::vec3 v2(2.0f, -40.0f, 1.0f);
//			m[2][0] = v2.x;
//			m[2][1] = v2.y;
//			m[2][2] = v2.z;
//			Assert::AreEqual<cgmath::vec3>(cgmath::vec3(17.0f, -142.0f, 4.0f), m * v1);
//
//			cgmath::vec3 v3(-3.0f, 0.0f, 8.0f);
//			m[1][0] = -2.0f;
//			m[0][1] = -3.0f;
//			m[0][2] = -7.0f;
//			Assert::AreEqual<cgmath::vec3>(cgmath::vec3(7.0f, -311.0f, 29.0f), m * v3);
//
//			cgmath::vec3 v4;
//			Assert::AreEqual<cgmath::vec3>(cgmath::vec3(), m * v4);
//
//			cgmath::mat3 m2;
//			Assert::AreEqual<cgmath::vec3>(v4, m2 * v2);
//
//			v4[0] = 1.0f;
//			v4[1] = 0.0f;
//			v4[2] = 1.0f;
//
//			m2[0][0] = cos(3.14159f);	m2[1][0] = -sin(3.14159f);	m2[2][0] = 0.0f;
//			m2[0][1] = sin(3.14159f);	m2[1][1] = cos(3.14159f);	m2[2][1] = 0.0f;
//			m2[0][2] = 0.0f;			m2[1][2] = 0.0f;			m2[2][2] = 1.0f;
//			Assert::AreEqual(-1.0f, (m2 * v4).x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, (m2 * v4).y, 0.00001f);
//			Assert::AreEqual(1.0f, (m2 * v4).z, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(Mat3xMat3)
//		{
//			cgmath::mat3 m1;
//			cgmath::mat3 m2(1.0f);
//
//			Assert::AreEqual<cgmath::mat3>(m1, m1 * m2);
//			Assert::AreNotEqual<cgmath::mat3>(m2, m2 * m1);
//
//			m1[0][0] = 1.0f;	m1[1][0] = 2.0f;	m1[2][0] = 3.0f;
//			m1[0][1] = 4.0f;	m1[1][1] = 5.0f;	m1[2][1] = 6.0f;
//			m1[0][2] = 7.0f;	m1[1][2] = 8.0f;	m1[2][2] = 9.0f;
//
//			m2[0][0] = -1.0f;	m2[1][0] = -2.0f;	m2[2][0] = -3.0f;
//			m2[0][1] = -4.0f;	m2[1][1] = -5.0f;	m2[2][1] = -6.0f;
//			m2[0][2] = -7.0f;	m2[1][2] = -8.0f;	m2[2][2] = -9.0f;
//
//			cgmath::mat3 r;
//			r[0][0] = -30.0f;	r[1][0] = -36.0f;	r[2][0] = -42.0f;
//			r[0][1] = -66.0f;	r[1][1] = -81.0f;	r[2][1] = -96.0f;
//			r[0][2] = -102.0f;	r[1][2] = -126.0f;	r[2][2] = -150.0f;
//			Assert::AreEqual(r, m1 * m2);
//
//			m1[0][0] = 1.0f;	m1[1][0] = 2.0f;	m1[2][0] = 3.0f;
//			m1[0][1] = 4.0f;	m1[1][1] = 5.0f;	m1[2][1] = 6.0f;
//			m1[0][2] = 7.0f;	m1[1][2] = 8.0f;	m1[2][2] = 9.0f;
//
//			m2[0][0] = 10.0f;	m2[1][0] = 11.0f;	m2[2][0] = 12.0f;
//			m2[0][1] = 13.0f;	m2[1][1] = 14.0f;	m2[2][1] = 15.0f;
//			m2[0][2] = 16.0f;	m2[1][2] = 17.0f;	m2[2][2] = 18.0f;
//
//			r[0][0] = 84.0f;	r[1][0] = 90.0f;	r[2][0] = 96.0f;
//			r[0][1] = 201.0f;	r[1][1] = 216.0f;	r[2][1] = 231.0f;
//			r[0][2] = 318.0f;	r[1][2] = 342.0f;	r[2][2] = 366.0f;
//			Assert::AreEqual(r, m1 * m2);
//			Assert::AreNotEqual(r, m2 * m1);
//
//			r[0][0] = 138.0f;	r[1][0] = 171.0f;	r[2][0] = 204.0f;
//			r[0][1] = 174.0f;	r[1][1] = 216.0f;	r[2][1] = 258.0f;
//			r[0][2] = 210.0f;	r[1][2] = 261.0f;	r[2][2] = 312.0f;
//			Assert::AreEqual(r, m2 * m1);
//
//			cgmath::vec3 v1(2.0f, 0.0f, 1.0f);
//
//			float pi = 3.1415926535897932384626433832795f;
//			m1[0][0] = cos(pi);		m1[1][0] = -sin(pi);	m1[2][0] = 0.0f;
//			m1[0][1] = sin(pi);		m1[1][1] = cos(pi);		m1[2][1] = 0.0f;
//			m1[0][2] = 0.0f;		m1[1][2] = 0.0f;		m1[2][2] = 1.0f;
//
//			m2[0][0] = cos(pi);		m2[1][0] = -sin(pi);	m2[2][0] = 0.0f;
//			m2[0][1] = sin(pi);		m2[1][1] = cos(pi);		m2[2][1] = 0.0f;
//			m2[0][2] = 0.0f;		m2[1][2] = 0.0f;		m2[2][2] = 1.0f;
//			Assert::AreEqual(2.0f, (m1 * m2 * v1).x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, (m1 * m2 * v1).y, 0.000001f);
//			Assert::AreEqual(1.0f, (m1 * m2 * v1).z, std::numeric_limits<float>::epsilon());
//		}
//	};
//}