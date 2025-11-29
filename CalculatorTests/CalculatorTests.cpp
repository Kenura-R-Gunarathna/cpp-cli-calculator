#include "pch.h"
#include "CppUnitTest.h"
#include "../HelloWorld/Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
	TEST_CLASS(CalculatorTests) 
	{
	public:
		
		void AssertDouble(double expected, double actual) {
			Assert::AreEqual(expected, actual, 0.0001);
		}

		TEST_METHOD(TestAddition)
		{
			Calculator calc("2 + 3");
			AssertDouble(5.0, calc.solve());
		}

		TEST_METHOD(TestOrderOfOperations)
		{
			Calculator calc("2 + 3 * 4");
			AssertDouble(14.0, calc.solve());
		}

		TEST_METHOD(TestParentheses)
		{
			Calculator calc("(2 + 3) * 4");
			AssertDouble(20.0, calc.solve());
		}

		TEST_METHOD(TestNestedParantheses)
		{
			Calculator calc("((1 + 2) * (3 + 4)) / 7");
			AssertDouble(3.0, calc.solve());
		}

		TEST_METHOD(TestPower)
		{
			Calculator calc("2 ^ 3 ^ 2");
			AssertDouble(512.0, calc.solve());
		}

		TEST_METHOD(TestSineDegrees)
		{
			Calculator calc("sin(30, deg)");
			AssertDouble(0.5, calc.solve());
		}

		TEST_METHOD(TestSineRadians)
		{
			Calculator calc1("sin(3.14159265358979323846 / 2)");
			AssertDouble(1.0, calc1.solve());

			Calculator calc2("sin(3.14159265358979323846 / 2, rad)");
			AssertDouble(1.0, calc2.solve());
		}

		TEST_METHOD(TestLogBase10)
		{
			Calculator calc("log(100)");
			AssertDouble(2.0, calc.solve());
		}

		TEST_METHOD(TestLogCustomBase)
		{
			Calculator calc("log(8, 2)");
			AssertDouble(3.0, calc.solve());
		}

		TEST_METHOD(TestDivisionByZero)
		{
			Calculator calc("10 / 0");
			AssertDouble(0.0, calc.solve());
		}
	};
}
