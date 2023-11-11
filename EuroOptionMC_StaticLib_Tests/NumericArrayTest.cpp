#include "pch.h"

#include "CommonUtilities.h"
#include "CppUnitTest.h"
#include "DataFilterInclude.h"
#include "NumericArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data;

namespace unit_test1
{
	// Test class dedicated to NumericArray functionality.
	TEST_CLASS(NumericArrayTests)
	{
	public:
		// Test to ensure that default constructor creates an empty array.
		TEST_METHOD(ConstructorCreatesEmptyArray)
		{
			numeric_array arr; // Create a default numeric_array.
			Assert::AreEqual(static_cast<unsigned long>(0), arr.size()); // Expect size to be 0.
		}

		// Test to ensure that constructor initializes array with given size and default values.
		TEST_METHOD(ConstructorInitializesArrayWithGivenSize)
		{
			numeric_array arr(5); // Create a numeric_array with size 5.
			Assert::AreEqual(static_cast<unsigned long>(5), arr.size()); // Verify size is 5.
			// Check that each element is initialized to default value 0.0.
			for (unsigned long i = 0; i < 5; ++i)
			{
				Assert::AreEqual(0.0, arr[i]); // Each element should be 0.0 by default.
			}
		}

		// Test to verify arithmetic operations on NumericArray objects.
		TEST_METHOD(ArithmeticOperations)
		{
			numeric_array arr1(3); // Initialize a numeric array of size 3.
			numeric_array arr2(3); // Initialize another numeric array of size 3.

			// Populate arrays with initial values.
			arr1[0] = 1.0;
			arr2[0] = 2.0;
			arr1[1] = 2.0;
			arr2[1] = 3.0;
			arr1[2] = 3.0;
			arr2[2] = 4.0;

			// Test addition operator.
			arr1 += arr2; // Add arr2 values to arr1.
			Assert::AreEqual(3.0, arr1[0]);
			Assert::AreEqual(5.0, arr1[1]);
			Assert::AreEqual(7.0, arr1[2]);

			// Test subtraction operator.
			arr1 -= arr2; // Subtract arr2 values from arr1.
			Assert::AreEqual(1.0, arr1[0]);
			Assert::AreEqual(2.0, arr1[1]);
			Assert::AreEqual(3.0, arr1[2]);

			// Test multiplication operator.
			arr1 *= 2; // Multiply all arr1 elements by 2.
			Assert::AreEqual(2.0, arr1[0]);
			Assert::AreEqual(4.0, arr1[1]);
			Assert::AreEqual(6.0, arr1[2]);

			// Test division operator.
			arr1 /= 2; // Divide all arr1 elements by 2.
			Assert::AreEqual(1.0, arr1[0]);
			Assert::AreEqual(2.0, arr1[1]);
			Assert::AreEqual(3.0, arr1[2]);
		}

		// Test to verify that sum, min, and max functions work as expected.
		TEST_METHOD(SumMinAndMaxFunctions)
		{
			numeric_array arr(5); // Initialize a numeric array of size 5.
			// Assign values to array elements.
			arr[0] = 1.5;
			arr[1] = -2.5;
			arr[2] = 3.5;
			arr[3] = -4.5;
			arr[4] = 5.5;

			// Test sum function.
			Assert::AreEqual(3.5, arr.sum()); // Expect sum of all elements.
			// Test min function.
			Assert::AreEqual(-4.5, arr.min()); // Expect the minimum value among elements.
			// Test max function.
			Assert::AreEqual(5.5, arr.max()); // Expect the maximum value among elements.
		}

		// Test to verify that arithmetic operations with mismatched sizes throw exceptions.
		TEST_METHOD(ArithmeticOperationsMismatchedSizes)
		{
			numeric_array arr1(3); // Initialize a numeric array of size 3.
			const numeric_array arr2(4); // Initialize another numeric array of size 4.

			// Expect exception when adding arrays of different sizes.
			auto func1 = [&]() { arr1 += arr2; };
			Assert::ExpectException<std::runtime_error>(func1);

			// Expect exception when subtracting arrays of different sizes.
			auto func2 = [&]() { arr1 -= arr2; };
			Assert::ExpectException<std::runtime_error>(func2);
		}

		// Test to verify that division by zero throws an exception.
		TEST_METHOD(DivisionByZeroThrows)
		{
			numeric_array arr(3); // Initialize a numeric array of size 3.
			// Assign non-zero values to array elements.
			arr[0] = 1.0;
			arr[1] = 2.0;
			arr[2] = 3.0;

			// Expect exception when dividing by zero.
			auto func = [&]() { arr /= 0.0; };
			Assert::ExpectException<std::runtime_error>(func);
		}

		// Test to verify that non-member arithmetic operators function correctly.
		TEST_METHOD(NonMemberOperators)
		{
			numeric_array arr1(3); // Initialize a numeric array of size 3.
			numeric_array arr2(3); // Initialize another numeric array of size 3.

			// Populate arrays with initial values.
			arr1[0] = 1.0;
			arr2[0] = 2.0;
			arr1[1] = 2.0;
			arr2[1] = 3.0;
			arr1[2] = 3.0;
			arr2[2] = 4.0;

			// Test non-member addition operator.
			numeric_array arr3 = arr1 + arr2; // Add arr2 to arr1 and store in a new array arr3.
			Assert::AreEqual(3.0, arr3[0]);
			Assert::AreEqual(5.0, arr3[1]);
			Assert::AreEqual(7.0, arr3[2]);

			// Test non-member subtraction operator.
			numeric_array arr4 = arr1 - arr2; // Subtract arr2 from arr1 and store in a new array arr4.
			Assert::AreEqual(-1.0, arr4[0]);
			Assert::AreEqual(-1.0, arr4[1]);
			Assert::AreEqual(-1.0, arr4[2]);
		}
	};
}
