#include "stdafx.h"
#include "CppUnitTest.h"

#include "vec3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			static std::wstring ToString<cgmath::vec3>(const cgmath::vec3& v)
			{
				return L"(" + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L", " + std::to_wstring(v.z) + L")";
			}
		}
	}
}

namespace MathTest
{
	TEST_CLASS(vec3_test)
	{
	public:

		TEST_METHOD(ConstructorTest)
		{
			cgmath::vec3 a;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 b(2.0f, -4.0f, 29.0f);
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(IndexTest)
		{
			cgmath::vec3 a;
			Assert::AreEqual(0.0f, a[0], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a[1], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a[2], std::numeric_limits<float>::epsilon());

			a[0] = -1.0f;
			a[1] = 3.0f;
			a[2] = -5.0f;
			Assert::AreEqual(-1.0f, a[0], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(3.0f, a[1], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-5.0f, a[2], std::numeric_limits<float>::epsilon());

			cgmath::vec3 b(-5.0f, 19.0f, 23.0f);
			Assert::AreEqual(-5.0f, b[0], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(19.0f, b[1], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(23.0f, b[2], std::numeric_limits<float>::epsilon());

			b[0] = 10.0f;
			b[1] = -6.0f;
			b[2] = 2.5f;
			Assert::AreEqual(10.0f, b[0], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, b[1], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.5f, b[2], std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(TimesEqualsTest)
		{
			cgmath::vec3 a;
			a *= 5.0f;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 b(1.0f, -2.0f, 4.0f);
			b *= 5.0f;
			Assert::AreEqual(5.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-10.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(20.0f, b.z, std::numeric_limits<float>::epsilon());

			b *= -2.0f;
			Assert::AreEqual(-10.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(20.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-40.0f, b.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(OverEqualsTest)
		{
			cgmath::vec3 a;
			a /= 2.0f;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 b(-10.0f, 20.0f, -120.0f);
			b /= 5.0f;
			Assert::AreEqual(-2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(4.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-24.0f, b.z, std::numeric_limits<float>::epsilon());

			b /= -2.0f;
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-2.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(12.0f, b.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(PlusEqualsTest)
		{
			cgmath::vec3 a;
			cgmath::vec3 b(2.0f, -3.0f, 5.0f);
			a += b;
			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, b.z, std::numeric_limits<float>::epsilon());

			a += b;
			Assert::AreEqual(4.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(10.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, b.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 c(-6.0f, 8.0f, 2.0f);
			a += c;
			Assert::AreEqual(-2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(12.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(8.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, c.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(MinusEqualsTest)
		{
			cgmath::vec3 a;
			cgmath::vec3 b(2.0f, -3.0f, 5.0f);
			a -= b;
			Assert::AreEqual(-2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(3.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-5.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, b.z, std::numeric_limits<float>::epsilon());

			a -= b;
			Assert::AreEqual(-4.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(6.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-10.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, b.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 c(-6.0f, 8.0f, 2.0f);
			a -= c;
			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-12.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(8.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, c.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(EqualityTest)
		{
			cgmath::vec3 a;
			cgmath::vec3 b;
			Assert::IsTrue(a == b);

			cgmath::vec3 c(1.0f, 2.0f, -5.0f);
			Assert::IsTrue(a == b);
			Assert::IsFalse(a == c);
			Assert::IsFalse(b == c);

			cgmath::vec3 d(-1.0f, 2.0f, 5.0f);
			Assert::IsTrue(a == b);
			Assert::IsFalse(a == c);
			Assert::IsFalse(a == d);
			Assert::IsFalse(b == c);
			Assert::IsFalse(b == d);
			Assert::IsFalse(c == d);

			cgmath::vec3 e(1.0f, 2.0f, -5.0f);
			Assert::IsTrue(a == b);
			Assert::IsFalse(a == c);
			Assert::IsFalse(a == d);
			Assert::IsFalse(a == e);
			Assert::IsFalse(b == c);
			Assert::IsFalse(b == d);
			Assert::IsFalse(b == e);
			Assert::IsFalse(c == d);
			Assert::IsTrue(c == e);
			Assert::IsFalse(d == e);
		}

		TEST_METHOD(InstanceMagnitudeTest)
		{
			cgmath::vec3 a;
			Assert::AreEqual(0.0f, a.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 b(1.0f, 0.0f, 0.0f);
			Assert::AreEqual(1.0f, b.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 c(0.0f, 1.0f, 0.0f);
			Assert::AreEqual(1.0f, c.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 d(0.0f, 0.0f, 1.0f);
			Assert::AreEqual(1.0f, d.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, d.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, d.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 e(5.0f, -4.0f, 2.0f);
			Assert::AreEqual(sqrt(45.0f), e.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, e.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, e.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, e.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(InstanceNormalizeTest)
		{
			cgmath::vec3 a;
			a.normalize();
			Assert::IsTrue(std::isnan(a.x));
			Assert::IsTrue(std::isnan(a.y));
			Assert::IsTrue(std::isnan(a.z));

			cgmath::vec3 b(1.0f, 0.0f, 0.0f);
			b.normalize();
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 c(0.0f, 1.0f, 0.0f);
			c.normalize();
			Assert::AreEqual(0.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 d(0.0f, 0.0f, 1.0f);
			d.normalize();
			Assert::AreEqual(0.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, d.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, d.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 e(1.0f, -4.0f, 29.0f);
			e.normalize();
			Assert::AreEqual(1.0f / sqrt(858.0f), e.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f / sqrt(858.0f), e.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f / sqrt(858.0f), e.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 f(1.0f, 4.0f, 8.0f);
			f.normalize();
			Assert::AreEqual(1.0f / 9.0f, f.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(4.0f / 9.0f, f.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(8.0f / 9.0f, f.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(StaticMagnitudeTest)
		{
			cgmath::vec3 a;
			Assert::AreEqual(0.0f, cgmath::vec3::magnitude(a), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 b(1.0f, 0.0f, 0.0f);
			Assert::AreEqual(1.0f, cgmath::vec3::magnitude(b), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 c(0.0f, 1.0f, 0.0f);
			Assert::AreEqual(1.0f, cgmath::vec3::magnitude(c), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 d(0.0f, 0.0f, 1.0f);
			Assert::AreEqual(1.0f, cgmath::vec3::magnitude(d), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, d.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, d.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 e(5.0f, -4.0f, 2.0f);
			Assert::AreEqual(sqrt(45.0f), cgmath::vec3::magnitude(e), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, e.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, e.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, e.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(StaticNormalizeTest)
		{
			cgmath::vec3 a;
			cgmath::vec3 b = cgmath::vec3::normalize(a);
			Assert::IsTrue(std::isnan(b.x));
			Assert::IsTrue(std::isnan(b.y));
			Assert::IsTrue(std::isnan(b.z));
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 c(1.0f, 0.0f, 0.0f);
			Assert::AreEqual(1.0f, cgmath::vec3::normalize(c).x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec3::normalize(c).y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec3::normalize(c).z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 d(0.0f, 1.0f, 0.0f);
			Assert::AreEqual(0.0f, cgmath::vec3::normalize(d).x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, cgmath::vec3::normalize(d).y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec3::normalize(d).z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, d.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, d.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 e(0.0f, 0.0f, 1.0f);
			Assert::AreEqual(0.0f, cgmath::vec3::normalize(e).x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec3::normalize(e).y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, cgmath::vec3::normalize(e).z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, e.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, e.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, e.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 f(1.0f, -4.0f, 29.0f);
			Assert::AreEqual(1.0f / sqrt(858.0f), cgmath::vec3::normalize(f).x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f / sqrt(858.0f), cgmath::vec3::normalize(f).y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f / sqrt(858.0f), cgmath::vec3::normalize(f).z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, f.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, f.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, f.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 g(1.0f, 4.0f, 8.0f);
			Assert::AreEqual(1.0f / 9.0f, cgmath::vec3::normalize(g).x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(4.0f / 9.0f, cgmath::vec3::normalize(g).y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(8.0f / 9.0f, cgmath::vec3::normalize(g).z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, g.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(4.0f, g.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(8.0f, g.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(StaticDotTest)
		{
			cgmath::vec3 a;
			cgmath::vec3 b;
			Assert::AreEqual(0.0f, cgmath::vec3::dot(a, b), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.z, std::numeric_limits<float>::epsilon());

			a.x = 1.0f;
			a.y = 7.0f;
			a.z = -3.0f;
			Assert::AreEqual(0.0f, cgmath::vec3::dot(a, b), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(7.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.z, std::numeric_limits<float>::epsilon());

			b.x = -3.0f;
			b.y = -2.0f;
			b.z = 4.0f;
			Assert::AreEqual(-29.0f, cgmath::vec3::dot(a, b), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(7.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-2.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(4.0f, b.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 c(1.0f, 0.0f, 0.0f);
			cgmath::vec3 d(-1.0f, 0.0f, 0.0f);
			cgmath::vec3 e(0.0f, 1.0f, 0.0f);
			cgmath::vec3 f(0.0f, -1.0f, 0.0f);
			cgmath::vec3 g(0.0f, 0.0, 1.0f);
			cgmath::vec3 h(0.0f, 0.0f, -1.0f);

			Assert::AreEqual(1.0f, cgmath::vec3::dot(c, c), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-1.0f, cgmath::vec3::dot(c, d), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec3::dot(c, e), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec3::dot(c, f), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec3::dot(c, g), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec3::dot(c, h), std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(StaticCrossTest)
		{
			cgmath::vec3 a(1.0f, 0.0f, 0.0f);
			cgmath::vec3 b(-1.0f, 0.0f, 0.0f);
			cgmath::vec3 c(0.0f, 1.0f, 0.0f);
			cgmath::vec3 d(0.0f, -1.0f, 0.0f);
			cgmath::vec3 e(0.0f, 0.0, 1.0f);
			cgmath::vec3 f(0.0f, 0.0f, -1.0f);
			cgmath::vec3 g;

			Assert::AreEqual<cgmath::vec3>(g, cgmath::vec3::cross(a, a));
			Assert::AreEqual<cgmath::vec3>(g, cgmath::vec3::cross(a, b));
			Assert::AreEqual<cgmath::vec3>(e, cgmath::vec3::cross(a, c));
			Assert::AreEqual<cgmath::vec3>(f, cgmath::vec3::cross(a, d));
			Assert::AreEqual<cgmath::vec3>(d, cgmath::vec3::cross(a, e));
			Assert::AreEqual<cgmath::vec3>(c, cgmath::vec3::cross(a, f));
			Assert::AreEqual<cgmath::vec3>(g, cgmath::vec3::cross(a, g));
		}

		TEST_METHOD(StreamExtractionTest)
		{
			std::stringstream ss1;
			cgmath::vec3 a;
			ss1 << a;
			std::string vecstring1 = ss1.rdbuf()->str();
			Assert::AreEqual<std::string>("(0, 0, 0)", vecstring1);

			std::stringstream ss2;
			cgmath::vec3 b(5.0f, -10.0f, 1.0f);
			ss2 << b;
			std::string vecstring2 = ss2.rdbuf()->str();
			Assert::AreEqual<std::string>("(5, -10, 1)", vecstring2);
		}

		TEST_METHOD(MultiplicationTest)
		{
			cgmath::vec3 a;
			a = a * 5.0f;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 b(1.0f, -2.0f, 7.0f);
			b = b * 5.0f;
			Assert::AreEqual(5.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-10.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(35.0f, b.z, std::numeric_limits<float>::epsilon());

			b = b * -2.0f;
			Assert::AreEqual(-10.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(20.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-70.0f, b.z, std::numeric_limits<float>::epsilon());

			a.x = 2.0f;
			a.y = -7.0f;
			a.z = 3.0f;
			b = -2.0f * a;
			Assert::AreEqual(-4.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(14.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, b.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-7.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(3.0f, a.z, std::numeric_limits<float>::epsilon());

			a.x = 2.0f;
			a.y = -7.0f;
			a.z = 3.0f;
			b = (-2.0f * a) * 2.0f;
			Assert::AreEqual(-8.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(28.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-12.0f, b.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-7.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(3.0f, a.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(DivisionTest)
		{
			cgmath::vec3 a;
			a = a / 2.0f;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 b(-10.0f, 20.0f, -30.0f);
			b = b / 5.0f;
			Assert::AreEqual(-2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(4.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, b.z, std::numeric_limits<float>::epsilon());

			b = b / -2.0f;
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-2.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(3.0f, b.z, std::numeric_limits<float>::epsilon());

			a.x = -4.0f;
			a.y = 14.0f;
			a.z = -32.0f;
			b = a / -2.0f;
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-7.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(16.0f, b.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(14.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-32.0f, a.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(AdditionTest)
		{
			cgmath::vec3 a(1.0f, 2.0f, -34.0f);
			cgmath::vec3 b(29.0f, -62.0f, 27.0f);
			cgmath::vec3 c = a + b;
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-34.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(27.0f, b.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(30.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-60.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-7.0f, c.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 d = c + a + b;
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-34.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(27.0f, b.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(30.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-60.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-7.0f, c.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(60.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-120.0f, d.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-14.0f, d.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(SubstractionTest)
		{
			cgmath::vec3 a(1.0f, 2.0f, -34.0f);
			cgmath::vec3 b(29.0f, -62.0f, 27.0f);
			cgmath::vec3 c = a - b;
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-34.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(27.0f, b.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-28.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(64.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-61.0f, c.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 d = c - a - b;
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-34.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(27.0f, b.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-28.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(64.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-61.0f, c.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-58.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(124.0f, d.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-54.0f, d.z, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(NegationTest)
		{
			cgmath::vec3 a;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 b = -a;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.z, std::numeric_limits<float>::epsilon());

			cgmath::vec3 c(-30.0f, 28.0f, -65.0f);
			cgmath::vec3 d = -c;
			Assert::AreEqual(-30.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(28.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-65.0f, c.z, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(30.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-28.0f, d.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(65.0f, d.z, std::numeric_limits<float>::epsilon());
		}
	};
}