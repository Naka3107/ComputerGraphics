#include "stdafx.h"
#include "CppUnitTest.h"

#include "vec2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			static std::wstring ToString<cgmath::vec2>(const cgmath::vec2& v)
			{
				return L"(" + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L")";
			}
		}
	}
}

namespace MathTest
{
	TEST_CLASS(vec2_test)
	{
	public:

		TEST_METHOD(ConstructorTest)
		{
			cgmath::vec2 a;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 b(2.0f, -4.0f);
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, b.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(IndexTest)
		{
			cgmath::vec2 a;
			Assert::AreEqual(0.0f, a[0], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a[1], std::numeric_limits<float>::epsilon());

			a[0] = -1.0f;
			a[1] = 3.0f;
			Assert::AreEqual(-1.0f, a[0], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(3.0f, a[1], std::numeric_limits<float>::epsilon());

			cgmath::vec2 b(-5.0f, 19.0f);
			Assert::AreEqual(-5.0f, b[0], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(19.0f, b[1], std::numeric_limits<float>::epsilon());

			b[0] = 10.0f;
			b[1] = -6.0f;
			Assert::AreEqual(10.0f, b[0], std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, b[1], std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(TimesEqualsTest)
		{
			cgmath::vec2 a;
			a *= 5.0f;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 b(1.0f, -2.0f);
			b *= 5.0f;
			Assert::AreEqual(5.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-10.0f, b.y, std::numeric_limits<float>::epsilon());
			b *= -2.0f;
			Assert::AreEqual(-10.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(20.0f, b.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(OverEqualsTest)
		{
			cgmath::vec2 a;
			a /= 2.0f;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 b(-10.0f, 20.0f);
			b /= 5.0f;
			Assert::AreEqual(-2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(4.0f, b.y, std::numeric_limits<float>::epsilon());
			b /= -2.0f;
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-2.0f, b.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(PlusEqualsTest)
		{
			cgmath::vec2 a;
			cgmath::vec2 b(2.0f, -3.0f);
			a += b;
			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());

			a += b;
			Assert::AreEqual(4.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 c(-6.0f, 8.0f);
			a += c;
			Assert::AreEqual(-2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(8.0f, c.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(MinusEqualsTest)
		{
			cgmath::vec2 a;
			cgmath::vec2 b(2.0f, -3.0f);
			a -= b;
			Assert::AreEqual(-2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(3.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());

			a -= b;
			Assert::AreEqual(-4.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(6.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 c(-6.0f, 8.0f);
			a -= c;
			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-6.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(8.0f, c.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(EqualityTest)
		{
			cgmath::vec2 a;
			cgmath::vec2 b;
			Assert::IsTrue(a == b);

			cgmath::vec2 c(1.0f, 2.0f);
			Assert::IsTrue(a == b);
			Assert::IsFalse(a == c);
			Assert::IsFalse(b == c);

			cgmath::vec2 d(-1.0f, 2.0f);
			Assert::IsTrue(a == b);
			Assert::IsFalse(a == c);
			Assert::IsFalse(a == d);
			Assert::IsFalse(b == c);
			Assert::IsFalse(b == d);
			Assert::IsFalse(c == d);

			cgmath::vec2 e(1.0f, 2.0f);
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
			cgmath::vec2 a;
			Assert::AreEqual(0.0f, a.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 b(1.0f, 0.0f);
			Assert::AreEqual(1.0f, b.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 c(0.0f, 1.0f);
			Assert::AreEqual(1.0f, c.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, c.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 d(5.0f, -4.0f);
			Assert::AreEqual(sqrt(41.0f), d.magnitude(), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, d.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(InstanceNormalizeTest)
		{
			cgmath::vec2 a;
			a.normalize();
			Assert::IsTrue(std::isnan(a.x));
			Assert::IsTrue(std::isnan(a.y));

			cgmath::vec2 b(1.0f, 0.0f);
			b.normalize();
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 c(0.0f, 1.0f);
			c.normalize();
			Assert::AreEqual(0.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, c.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 d(1.0f, -4.0f);
			d.normalize();
			Assert::AreEqual(1.0f / sqrt(17.0f), d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f / sqrt(17.0f), d.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(StaticMagnitudeTest)
		{
			cgmath::vec2 a;
			Assert::AreEqual(0.0f, cgmath::vec2::magnitude(a), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 b(1.0f, 0.0f);
			Assert::AreEqual(1.0f, cgmath::vec2::magnitude(b), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 c(0.0f, 1.0f);
			Assert::AreEqual(1.0f, cgmath::vec2::magnitude(c), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, c.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 d(5.0f, -4.0f);
			Assert::AreEqual(sqrt(41.0f), cgmath::vec2::magnitude(d), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(5.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, d.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(StaticNormalizeTest)
		{
			cgmath::vec2 a;
			cgmath::vec2 b = cgmath::vec2::normalize(a);
			Assert::IsTrue(std::isnan(b.x));
			Assert::IsTrue(std::isnan(b.y));
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 c(1.0f, 0.0f);
			Assert::AreEqual(1.0f, cgmath::vec2::normalize(c).x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, cgmath::vec2::normalize(c).y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, c.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 d(0.0f, 1.0f);
			Assert::AreEqual(0.0f, cgmath::vec2::normalize(d).x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, cgmath::vec2::normalize(d).y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, d.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 e(1.0f, -4.0f);
			Assert::AreEqual(1.0f / sqrt(17.0f), cgmath::vec2::normalize(e).x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f / sqrt(17.0f), cgmath::vec2::normalize(e).y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, e.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, e.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(StaticDotTest)
		{
			cgmath::vec2 a;
			cgmath::vec2 b;
			Assert::AreEqual(0.0f, cgmath::vec2::dot(a, b), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());

			a.x = 1.0f;
			a.y = 7.0f;
			Assert::AreEqual(0.0f, cgmath::vec2::dot(a, b), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(7.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());

			b.x = -3.0f;
			b.y = -2.0f;
			Assert::AreEqual(-17.0f, cgmath::vec2::dot(a, b), std::numeric_limits<float>::epsilon());
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(7.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-3.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-2.0f, b.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(StreamExtractionTest)
		{
			std::stringstream ss1;
			cgmath::vec2 a;
			ss1 << a;
			std::string vecstring1 = ss1.rdbuf()->str();
			Assert::AreEqual<std::string>("(0, 0)", vecstring1);

			std::stringstream ss2;
			cgmath::vec2 b(5.0f, -10.0f);
			ss2 << b;
			std::string vecstring2 = ss2.rdbuf()->str();
			Assert::AreEqual<std::string>("(5, -10)", vecstring2);
		}

		TEST_METHOD(MultiplicationTest)
		{
			cgmath::vec2 a;
			a = a * 5.0f;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 b(1.0f, -2.0f);
			b = b * 5.0f;
			Assert::AreEqual(5.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-10.0f, b.y, std::numeric_limits<float>::epsilon());
			b = b * -2.0f;
			Assert::AreEqual(-10.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(20.0f, b.y, std::numeric_limits<float>::epsilon());

			a.x = 2.0f;
			a.y = -7.0f;
			b = -2.0f * a;
			Assert::AreEqual(-4.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(14.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-7.0f, a.y, std::numeric_limits<float>::epsilon());

			a.x = 2.0f;
			a.y = -7.0f;
			b = (-2.0f * a) * 2.0f;
			Assert::AreEqual(-8.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(28.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-7.0f, a.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(DivisionTest)
		{
			cgmath::vec2 a;
			a = a / 2.0f;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 b(-10.0f, 20.0f);
			b = b / 5.0f;
			Assert::AreEqual(-2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(4.0f, b.y, std::numeric_limits<float>::epsilon());
			b = b / -2.0f;
			Assert::AreEqual(1.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-2.0f, b.y, std::numeric_limits<float>::epsilon());

			a.x = -4.0f;
			a.y = 14.0f;
			b = a / -2.0f;
			Assert::AreEqual(2.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-7.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-4.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(14.0f, a.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(AdditionTest)
		{
			cgmath::vec2 a(1.0f, 2.0f);
			cgmath::vec2 b(29.0f, -62.0f);
			cgmath::vec2 c = a + b;
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(30.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-60.0f, c.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 d = c + a + b;
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(30.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-60.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(60.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-120.0f, d.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(SubstractionTest)
		{
			cgmath::vec2 a(1.0f, 2.0f);
			cgmath::vec2 b(29.0f, -62.0f);
			cgmath::vec2 c = a - b;
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-28.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(64.0f, c.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 d = c - a - b;
			Assert::AreEqual(1.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(2.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(29.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-62.0f, b.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-28.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(64.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-58.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(124.0f, d.y, std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(NegationTest)
		{
			cgmath::vec2 a;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 b = -a;
			Assert::AreEqual(0.0f, a.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, a.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(0.0f, b.y, std::numeric_limits<float>::epsilon());

			cgmath::vec2 c(-30.0f, 28.0f);
			cgmath::vec2 d = -c;
			Assert::AreEqual(-30.0f, c.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(28.0f, c.y, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(30.0f, d.x, std::numeric_limits<float>::epsilon());
			Assert::AreEqual(-28.0f, d.y, std::numeric_limits<float>::epsilon());
		}
	};
}