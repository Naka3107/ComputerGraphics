#include "stdafx.h"
#include "CppUnitTest.h"

//#include "vec4.h"
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
//		}
//	}
//}
//
//namespace MathTest
//{
//	TEST_CLASS(vec4_test)
//	{
//	public:
//
//		TEST_METHOD(ConstructorTest)
//		{
//			cgmath::vec4 a;
//			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 b(2.0f, -4.0f, 29.0f, -35.0f);
//			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-4.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(29.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-35.0f, b.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(IndexTest)
//		{
//			cgmath::vec4 a;
//			Assert::AreEqual(0.0f, a[0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a[3], std::numeric_limits<float>::epsilon());
//
//			a[0] = -1.0f;
//			a[1] = 3.0f;
//			a[2] = -5.0f;
//			a[3] = 9.0f;
//			Assert::AreEqual(-1.0f, a[0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, a[1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-5.0f, a[2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(9.0f, a[3], std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 b(-5.0f, 19.0f, 23.0f, -32.0f);
//			Assert::AreEqual(-5.0f, b[0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(19.0f, b[1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(23.0f, b[2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-32.0f, b[3], std::numeric_limits<float>::epsilon());
//
//			b[0] = 10.0f;
//			b[1] = -6.0f;
//			b[2] = 2.5f;
//			b[3] = -6.8f;
//			Assert::AreEqual(10.0f, b[0], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-6.0f, b[1], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.5f, b[2], std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-6.8f, b[3], std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(TimesEqualsTest)
//		{
//			cgmath::vec4 a;
//			a *= 5.0f;
//			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 b(1.0f, -2.0f, 4.0f, -5.0f);
//			b *= 5.0f;
//			Assert::AreEqual(5.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-10.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(20.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-25.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			b *= -2.0f;
//			Assert::AreEqual(-10.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(20.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-40.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(50.0f, b.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(OverEqualsTest)
//		{
//			cgmath::vec4 a;
//			a /= 2.0f;
//			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 b(-10.0f, 20.0f, -120.0f, 35.0f);
//			b /= 5.0f;
//			Assert::AreEqual(-2.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(4.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-24.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(7.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			b /= -2.0f;
//			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-2.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(12.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f / 2.0f, b.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(PlusEqualsTest)
//		{
//			cgmath::vec4 a;
//			cgmath::vec4 b(2.0f, -3.0f, 5.0f, -13.0f);
//			a += b;
//			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-3.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			a += b;
//			Assert::AreEqual(4.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-6.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(10.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-26.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 c(-6.0f, 8.0f, 2.0f, -15.0f);
//			a += c;
//			Assert::AreEqual(-2.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(12.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-41.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-6.0f, c.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(8.0f, c.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, c.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-15.0f, c.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(MinusEqualsTest)
//		{
//			cgmath::vec4 a;
//			cgmath::vec4 b(2.0f, -3.0f, 5.0f, -13.0f);
//			a -= b;
//			Assert::AreEqual(-2.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-5.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(13.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			a -= b;
//			Assert::AreEqual(-4.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(6.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-10.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(26.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(5.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 c(-6.0f, 8.0f, 2.0f, -15.0f);
//			a -= c;
//			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-2.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-12.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(41.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-6.0f, c.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(8.0f, c.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, c.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-15.0f, c.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(EqualityTest)
//		{
//			cgmath::vec4 a;
//			cgmath::vec4 b;
//			Assert::IsTrue(a == b);
//
//			cgmath::vec4 c(1.0f, 2.0f, -5.0f, -3.0f);
//			Assert::IsTrue(a == b);
//			Assert::IsFalse(a == c);
//			Assert::IsFalse(b == c);
//
//			cgmath::vec4 d(-1.0f, 2.0f, 5.0f, -3.0f);
//			Assert::IsTrue(a == b);
//			Assert::IsFalse(a == c);
//			Assert::IsFalse(a == d);
//			Assert::IsFalse(b == c);
//			Assert::IsFalse(b == d);
//			Assert::IsFalse(c == d);
//
//			cgmath::vec4 e(1.0f, 2.0f, -5.0f, -3.0f);
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
//		TEST_METHOD(StreamExtractionTest)
//		{
//			std::stringstream ss1;
//			cgmath::vec4 a;
//			ss1 << a;
//			std::string vecstring1 = ss1.rdbuf()->str();
//			Assert::AreEqual<std::string>("(0, 0, 0, 0)", vecstring1);
//
//			std::stringstream ss2;
//			cgmath::vec4 b(5.0f, -10.0f, 1.0f, -4.99f);
//			ss2 << b;
//			std::string vecstring2 = ss2.rdbuf()->str();
//			Assert::AreEqual<std::string>("(5, -10, 1, -4.99)", vecstring2);
//		}
//
//		TEST_METHOD(MultiplicationTest)
//		{
//			cgmath::vec4 a;
//			a = a * 5.0f;
//			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 b(1.0f, -2.0f, 7.0f, -4.0f);
//			b = b * 5.0f;
//			Assert::AreEqual(5.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-10.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(35.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-20.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			b = b * -2.0f;
//			Assert::AreEqual(-10.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(20.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-70.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(40.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			a.x = 2.0f;
//			a.y = -7.0f;
//			a.z = 3.0f;
//			a.w = 1.0f;
//			b = -2.0f * a;
//			Assert::AreEqual(-4.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(14.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-6.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-2.0f, b.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, a.w, std::numeric_limits<float>::epsilon());
//
//			a.x = 2.0f;
//			a.y = -7.0f;
//			a.z = 3.0f;
//			a.w = 1.0f;
//			b = (-2.0f * a) * 2.0f;
//			Assert::AreEqual(-8.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(28.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-12.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-4.0f, b.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, a.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(DivisionTest)
//		{
//			cgmath::vec4 a;
//			a = a / 2.0f;
//			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 b(-10.0f, 20.0f, -30.0f, 15.0f);
//			b = b / 5.0f;
//			Assert::AreEqual(-2.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(4.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-6.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			b = b / -2.0f;
//			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-2.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(3.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-3.0f / 2.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			a.x = -4.0f;
//			a.y = 14.0f;
//			a.z = -32.0f;
//			a.w = 1.0f;
//			b = a / -2.0f;
//			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(16.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-1.0f / 2.0f, b.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-4.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(14.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-32.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(1.0f, a.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(AdditionTest)
//		{
//			cgmath::vec4 a(1.0f, 2.0f, -34.0f, -17.0f);
//			cgmath::vec4 b(29.0f, -62.0f, 27.0f, -13.0f);
//			cgmath::vec4 c = a + b;
//			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-34.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-17.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(27.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, b.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(30.0f, c.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-60.0f, c.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, c.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-30.0f, c.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 d = c + a + b;
//			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-34.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-17.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(27.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, b.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(30.0f, c.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-60.0f, c.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-7.0f, c.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-30.0f, c.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(60.0f, d.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-120.0f, d.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-14.0f, d.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-60.0f, d.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(SubstractionTest)
//		{
//			cgmath::vec4 a(1.0f, 2.0f, -34.0f, -17.0f);
//			cgmath::vec4 b(29.0f, -62.0f, 27.0f, -13.0f);
//			cgmath::vec4 c = a - b;
//			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-34.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-17.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(27.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, b.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-28.0f, c.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(64.0f, c.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-61.0f, c.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-4.0f, c.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 d = c - a - b;
//			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-34.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-17.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(27.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, b.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-28.0f, c.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(64.0f, c.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-61.0f, c.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-4.0f, c.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-58.0f, d.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(124.0f, d.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-54.0f, d.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(26.0f, d.w, std::numeric_limits<float>::epsilon());
//		}
//
//		TEST_METHOD(NegationTest)
//		{
//			cgmath::vec4 a;
//			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 b = -a;
//			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, a.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(0.0f, b.w, std::numeric_limits<float>::epsilon());
//
//			cgmath::vec4 c(-30.0f, 28.0f, -65.0f, 13.0f);
//			cgmath::vec4 d = -c;
//			Assert::AreEqual(-30.0f, c.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(28.0f, c.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-65.0f, c.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(13.0f, c.w, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(30.0f, d.x, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-28.0f, d.y, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(65.0f, d.z, std::numeric_limits<float>::epsilon());
//			Assert::AreEqual(-13.0f, d.w, std::numeric_limits<float>::epsilon());
//		}
//	};
//}