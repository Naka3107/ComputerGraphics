#include "stdafx.h"
#include "CppUnitTest.h"

//#include <cmath>
//#include <limits>
//#include <locale>
//#include <codecvt>
//
//#include "vec4.h"
//#include "mat4.h"
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
//			static std::wstring ToString<cgmath::vec4>(const cgmath::vec4& v)
//			{
//				return L"(" + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L", " + std::to_wstring(v.z) + L", " + std::to_wstring(v.w) + L")";
//			}
//
//			template<>
//			static std::wstring ToString<cgmath::mat4>(const cgmath::mat4& m)
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
//	TEST_CLASS(mat4_test)
//	{
//	public:
//		TEST_METHOD(ConstructorTest)
//		{
//			cgmath::mat4 a;
//			Assert::AreEqual(0.0f, a[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[0][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[1][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[2][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[2][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[3][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[3][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[3][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[3][3], std::numeric_limits<float>::epsilon());
//
//			cgmath::mat4 b(1.0f);
//			Assert::AreEqual(1.0f, b[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[0][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, b[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[1][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, b[2][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[2][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[3][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[3][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b[3][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, b[3][3], std::numeric_limits<float>::epsilon());
//
//			cgmath::mat4 c(-7.0f);
//			Assert::AreEqual(-7.0f, c[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[0][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, c[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[1][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, c[2][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[2][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[3][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[3][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, c[3][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, c[3][3], std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 col1(0.0f, 1.0f, 2.0f, 3.0f);
//			cgmath::vec4 col2(4.0f, 5.0f, 6.0f, 7.0f);
//			cgmath::vec4 col3(8.0f, 9.0f, 10.0f, 11.0f);
//			cgmath::vec4 col4(12.0f, 13.0f, 14.0f, 15.0f);
//			cgmath::mat4 d(col1, col2, col3, col4);
//			for (auto& col : { 0, 1, 2, 3 })
//				for (auto& row : { 0, 1, 2, 3 })
//					Assert::AreEqual(col * 4.0f + row, d[col][row], std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(IndexTest)
//		{
//			cgmath::vec4 col1(0.0f, 1.0f, 2.0f, 3.0f);
//			cgmath::vec4 col2(4.0f, 5.0f, 6.0f, 7.0f);
//			cgmath::vec4 col3(8.0f, 9.0f, 10.0f, 11.0f);
//			cgmath::vec4 col4(12.0f, 13.0f, 14.0f, 15.0f);
//			cgmath::mat4 a(col1, col2, col3, col4);
//			for (auto& col : { 0, 1, 2, 3 })
//				for (auto& row : { 0, 1, 2, 3 })
//					Assert::AreEqual(col * 4.0f + row, a[col][row], std::numeric_limits<float>::epsilon());
//
//			a[0][0] = 1.0f + 22.0f;	a[1][0] -= 2.0f;		a[2][0] = 7.0f * 3.0f;	a[3][0] = 1.0f + 22.0f;
//			a[0][1] = 22.0f - 3.0f;	a[1][1] += 11.0f;		a[2][1] *= 3.0f;		a[3][1] = 22.0f - 3.0f;
//			a[0][2] = 18.0f;		a[1][2] = 6.0f / 3.0f;	a[2][2] /= 3.0f;		a[3][2] = 18.0f;
//			a[0][3] = 17.0f;		a[1][3] = 9.0f / 3.0f;	a[2][3] /= 3.0f;		a[3][3] = 38.0f;
//
//			Assert::AreEqual(1.0f + 22.0f, a[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(22.0f - 3.0f, a[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(18.0f, a[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(17.0f, a[0][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(4.0f - 2.0f, a[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f + 11.0f, a[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(6.0f / 3.0f, a[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(9.0f / 3.0f, a[1][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(7.0f * 3.0f, a[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(9.0f * 3.0f, a[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(10.0f / 3.0f, a[2][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(11.0f / 3.0f, a[2][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f + 22.0f, a[3][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(22.0f - 3.0f, a[3][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(18.0f, a[3][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(38.0f, a[3][3], std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(EqualityTest)
//		{
//			cgmath::mat4 a;
//			cgmath::mat4 b;
//			Assert::IsTrue(a == b);
//
//			cgmath::vec4 col1(1.0f, 2.0f, 3.0f, 1.0f);
//			cgmath::vec4 col2(4.0f, 5.0f, 6.0f, -2.0f);
//			cgmath::vec4 col3(7.0f, 8.0f, 9.0f, 3.0f);
//			cgmath::vec4 col4(7.0f, 8.0f, 9.0f, -4.0f);
//			cgmath::mat4 c(col1, col2, col3, col4);
//			Assert::IsTrue(a == b);
//			Assert::IsFalse(a == c);
//			Assert::IsFalse(b == c);
//
//			cgmath::mat4 d(-col1, col2, -col3, col4);
//			Assert::IsTrue(a == b);
//			Assert::IsFalse(a == c);
//			Assert::IsFalse(a == d);
//			Assert::IsFalse(b == c);
//			Assert::IsFalse(b == d);
//			Assert::IsFalse(c == d);
//
//			cgmath::mat4 e;
//			e[0] = col1;
//			e[1] = col2;
//			e[2] = col3;
//			e[3] = col4;
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
//		TEST_METHOD(InverseTest)
//		{
//			cgmath::mat4 a;
//			for (auto& i : { 0, 1, 2, 3 })
//				for (auto& j : { 0, 1, 2, 3 })
//					Assert::IsTrue(std::isnan(cgmath::mat4::inverse(a)[i][j]));
//
//			cgmath::mat4 b(1.0f);
//			Assert::AreEqual<cgmath::mat4>(b, cgmath::mat4::inverse(b));
//
//			cgmath::mat4 c(2.0f);
//			cgmath::mat4 d(0.5f);
//			Assert::AreEqual<cgmath::mat4>(d, cgmath::mat4::inverse(c));
//
//			cgmath::vec4 col1(1.0f, 4.0f, -7.0f, 1.0f);
//			cgmath::vec4 col2(2.0f, -5.0f, 8.0f, -2.0f);
//			cgmath::vec4 col3(3.0f, 6.0f, -9.0f, 3.0f);
//			cgmath::vec4 col4(4.0f, -7.0f, 10.0f, 1.0f);
//			cgmath::mat4 e(col1, col2, col3, col4);
//			cgmath::mat4 f = cgmath::mat4::inverse(e);
//			Assert::AreEqual(1.0f / 8.0f, f[0][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f / 4.0f, f[0][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f / 8.0f, f[0][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, f[0][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-23.0f / 20.0f, f[1][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f / 10.0f, f[1][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(43.0f / 60.0f, f[1][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-2.0f / 5.0f, f[1][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-33.0f / 40.0f, f[2][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f / 20.0f, f[2][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(53.0f / 120.0f, f[2][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-1.0f / 5.0f, f[2][3], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-3.0f / 10.0f, f[3][0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-2.0f / 5.0f, f[3][1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f / 10.0f, f[3][2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f / 5.0f, f[3][3], std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(StreamExtraction)
//		{
//			std::stringstream ss1;
//			cgmath::mat4 a;
//			ss1 << a;
//			std::string matstring1 = ss1.rdbuf()->str();
//			Assert::AreEqual<std::string>("0 0 0 0\n0 0 0 0\n0 0 0 0\n0 0 0 0", matstring1);
//
//			std::stringstream ss2;
//			cgmath::vec4 col1(1.0f, 2.0f, 3.0f, 4.0f);
//			cgmath::vec4 col2(5.0f, 6.0f, 7.0f, 8.0f);
//			cgmath::vec4 col3(9.0f, 10.0f, 11.0f, 12.0f);
//			cgmath::vec4 col4(13.0f, 14.0f, 15.0f, 16.0f);
//			cgmath::mat4 b(col1, col2, col3, col4);
//			ss2 << b;
//			std::string vecstring2 = ss2.rdbuf()->str();
//			Assert::AreEqual<std::string>("1 5 9 13\n2 6 10 14\n3 7 11 15\n4 8 12 16", vecstring2);
//		}
//
//		TEST_METHOD(Mat4xVec4)
//		{
//			cgmath::vec4 v1(3.0f, 6.0f, 4.0f, -2.0f);
//			cgmath::mat4 m(1.0f);
//			Assert::AreEqual<cgmath::vec4>(v1, m * v1);
//
//			m[0][0] *= 3.0f;
//			m[1][1] *= 3.0f;
//			m[2][2] *= 3.0f;
//			m[3][3] *= 3.0f;
//			Assert::AreEqual<cgmath::vec4>(v1 * 3.0f, m * v1);
//
//			cgmath::vec4 v2(2.0f, -40.0f, 1.0f, 1.0f);
//			m[2][0] = v2.x;
//			m[2][1] = v2.y;
//			m[2][2] = v2.z;
//			m[3][3] = v2.w;
//			Assert::AreEqual<cgmath::vec4>(cgmath::vec4(17.0f, -142.0f, 4.0f, -2.0f), m * v1);
//
//			cgmath::vec4 v3(-3.0f, 0.0f, 8.0f, 1.0f);
//			m[1][0] = -2.0f;
//			m[0][1] = -3.0f;
//			m[0][2] = -7.0f;
//			Assert::AreEqual<cgmath::vec4>(cgmath::vec4(7.0f, -311.0f, 29.0f, 1.0f), m * v3);
//
//			cgmath::vec4 v4;
//			Assert::AreEqual<cgmath::vec4>(cgmath::vec4(), m * v4);
//
//			cgmath::mat4 m2;
//			Assert::AreEqual<cgmath::vec4>(v4, m2 * v2);
//
//			v4[0] = 1.0f;
//			v4[1] = 0.0f;
//			v4[2] = 1.0f;
//
//			m2[0][0] = cos(3.14159f);	m2[1][0] = -sin(3.14159f);	m2[2][0] = 0.0f;	m2[3][0] = 0.0f;
//			m2[0][1] = sin(3.14159f);	m2[1][1] = cos(3.14159f);	m2[2][1] = 0.0f;	m2[3][1] = 0.0f;
//			m2[0][2] = 0.0f;			m2[1][2] = 0.0f;			m2[2][2] = 1.0f;	m2[3][2] = 0.0f;
//			m2[0][3] = 0.0f;			m2[1][3] = 0.0f;			m2[2][3] = 0.0f;	m2[3][3] = 1.0f;
//			Assert::AreEqual(-1.0f, (m2 * v4).x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, (m2 * v4).y, 0.00001f);
//			Assert::AreEqual(1.0f, (m2 * v4).z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, (m2 * v4).w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(Mat4xMat4)
//		{
//			cgmath::mat4 m1;
//			cgmath::mat4 m2(1.0f);
//
//			Assert::AreEqual<cgmath::mat4>(m1, m1 * m2);
//			Assert::AreNotEqual<cgmath::mat4>(m2, m2 * m1);
//
//			m1[0][0] = 1.0f;	m1[1][0] = 2.0f;	m1[2][0] = 3.0f;	m1[3][0] = 4.0f;
//			m1[0][1] = 5.0f;	m1[1][1] = 6.0f;	m1[2][1] = 7.0f;	m1[3][1] = 8.0f;
//			m1[0][2] = 9.0f;	m1[1][2] = 10.0f;	m1[2][2] = 11.0f;	m1[3][2] = 12.0f;
//			m1[0][3] = 13.0f;	m1[1][3] = 14.0f;	m1[2][3] = 15.0f;	m1[3][3] = 16.0f;
//
//			m2[0][0] = -1.0f;	m2[1][0] = -2.0f;	m2[2][0] = -3.0f;	m2[3][0] = -4.0f;
//			m2[0][1] = -5.0f;	m2[1][1] = -6.0f;	m2[2][1] = -7.0f;	m2[3][1] = -8.0f;
//			m2[0][2] = -9.0f;	m2[1][2] = -10.0f;	m2[2][2] = -11.0f;	m2[3][2] = -12.0f;
//			m2[0][3] = -13.0f;	m2[1][3] = -14.0f;	m2[2][3] = -15.0f;	m2[3][3] = -16.0f;
//
//			cgmath::mat4 r;
//			r[0][0] = -90.0f;	r[1][0] = -100.0f;	r[2][0] = -110.0f;	r[3][0] = -120.0f;
//			r[0][1] = -202.0f;	r[1][1] = -228.0f;	r[2][1] = -254.0f;	r[3][1] = -280.0f;
//			r[0][2] = -314.0f;	r[1][2] = -356.0f;	r[2][2] = -398.0f;	r[3][2] = -440.0f;
//			r[0][3] = -426.0f;	r[1][3] = -484.0f;	r[2][3] = -542.0f;	r[3][3] = -600.0f;
//			Assert::AreEqual<cgmath::mat4>(r, m1 * m2);
//
//			m1[0][0] = 1.0f;	m1[1][0] = 2.0f;	m1[2][0] = 3.0f;	m1[3][0] = 4.0f;
//			m1[0][1] = 5.0f;	m1[1][1] = 6.0f;	m1[2][1] = 7.0f;	m1[3][1] = 8.0f;
//			m1[0][2] = 9.0f;	m1[1][2] = 10.0f;	m1[2][2] = 11.0f;	m1[3][2] = 12.0f;
//			m1[0][3] = 13.0f;	m1[1][3] = 14.0f;	m1[2][3] = 15.0f;	m1[3][3] = 16.0f;
//
//			m2[0][0] = 17.0f;	m2[1][0] = 18.0f;	m2[2][0] = 19.0f;	m2[3][0] = 20.0f;
//			m2[0][1] = 21.0f;	m2[1][1] = 22.0f;	m2[2][1] = 23.0f;	m2[3][1] = 24.0f;
//			m2[0][2] = 25.0f;	m2[1][2] = 26.0f;	m2[2][2] = 27.0f;	m2[3][2] = 28.0f;
//			m2[0][3] = 29.0f;	m2[1][3] = 30.0f;	m2[2][3] = 31.0f;	m2[3][3] = 32.0f;
//
//			r[0][0] = 250.0f;	r[1][0] = 260.0f;	r[2][0] = 270.0f;	r[3][0] = 280.0f;
//			r[0][1] = 618.0f;	r[1][1] = 644.0f;	r[2][1] = 670.0f;	r[3][1] = 696.0f;
//			r[0][2] = 986.0f;	r[1][2] = 1028.0f;	r[2][2] = 1070.0f;	r[3][2] = 1112.0f;
//			r[0][3] = 1354.0f;	r[1][3] = 1412.0f;	r[2][3] = 1470.0f;	r[3][3] = 1528.0f;
//			Assert::AreEqual<cgmath::mat4>(r, m1 * m2);
//			Assert::AreNotEqual<cgmath::mat4>(r, m2 * m1);
//
//			r[0][0] = 538.0f;	r[1][0] = 612.0f;	r[2][0] = 686.0f;	r[3][0] = 760.0f;
//			r[0][1] = 650.0f;	r[1][1] = 740.0f;	r[2][1] = 830.0f;	r[3][1] = 920.0f;
//			r[0][2] = 762.0f;	r[1][2] = 868.0f;	r[2][2] = 974.0f;	r[3][2] = 1080.0f;
//			r[0][3] = 874.0f;	r[1][3] = 996.0f;	r[2][3] = 1118.0f;	r[3][3] = 1240.0f;
//			Assert::AreEqual<cgmath::mat4>(r, m2 * m1);
//
//			cgmath::vec4 v(2.0f, 0.0f, -1.0f, 1.0f);
//
//			float pi = 3.1415926535897932384626433832795f;
//			m1[0][0] = cos(pi);	m1[1][0] = -sin(pi);	m1[2][0] = 0.0f;	m1[3][0] = 0.0f;
//			m1[0][1] = sin(pi);	m1[1][1] = cos(pi);		m1[2][1] = 0.0f;	m1[3][1] = 0.0f;
//			m1[0][2] = 0.0f;	m1[1][2] = 0.0f;		m1[2][2] = 1.0f;	m1[3][2] = 0.0f;
//			m1[0][3] = 0.0f;	m1[1][3] = 0.0f;		m1[2][3] = 0.0f;	m1[3][3] = 1.0f;
//
//			m2[0][0] = cos(pi);	m2[1][0] = -sin(pi);	m2[2][0] = 0.0f;	m2[3][0] = 0.0f;
//			m2[0][1] = sin(pi);	m2[1][1] = cos(pi);		m2[2][1] = 0.0f;	m2[3][1] = 0.0f;
//			m2[0][2] = 0.0f;	m2[1][2] = 0.0f;		m2[2][2] = 1.0f;	m2[3][2] = 0.0f;
//			m2[0][3] = 0.0f;	m2[1][3] = 0.0f;		m2[2][3] = 0.0f;	m2[3][3] = 1.0f;
//
//			cgmath::vec4 res = m1 * m2 * v;
//			Assert::AreEqual(2.0f, v.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, v.y, 0.000001f);
//			Assert::AreEqual(-1.0f, v.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, v.w, std::numeric_limits<float>::epsilon());
//		}
//	};
//}