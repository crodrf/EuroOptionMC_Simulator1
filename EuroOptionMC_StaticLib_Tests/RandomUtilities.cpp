#include "pch.h"

#include <algorithm>
#include <numeric>

#include "CppUnitTest.h"
#include "IncludeRandom.h"
#include "NumericArray.h"
#include "TimeInterval.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace random_generators;

namespace unit_test1
{
	TEST_CLASS(CumulativeNormalTest)
	{
	public:
		// Test method for checking the accuracy of the cumulative normal distribution and its inverse
		TEST_METHOD(TestCumulativeNormalAndItsInverse)
		{
			// Test values for checking the distribution
			const std::vector<double> test_values = {-2.5, -1.5, -0.5, 0, 0.5, 1.5, 2.5};

			// Iterating through each test value
			for (const double original : test_values)
			{
				// Calculating cumulative distribution function (CDF) value
				const double cdf_value = cumulative_normal(original);

				// Calculating the inverse of the CDF
				const double inverse_value = inverse_cumulative_normal(cdf_value);

				// Asserting that the original value and the inverse of its CDF are equal within a tolerance
				Assert::AreEqual(original, inverse_value, 1e-5);
			}
		}

		// Test method for generating random numbers and checking their statistical properties
		TEST_METHOD(randomNumber)
		{
			// Initializing a unique pointer for random number generation with a seed
			std::unique_ptr<random_base> randomization = std::make_unique<random_park_miller>(20000);
			random_base_wrapper random_base_wrapper(std::move(randomization));
			numeric_array numbers(20000);
			random_base_wrapper.get_gaussians(numbers);

			// Calculating the sum of the generated numbers
			const double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
			// Calculating the mean of the numbers
			const double mean = sum / numbers.size();

			// Calculating the sum of squares of the numbers
			const double sq_sum = std::inner_product(numbers.begin(), numbers.end(), numbers.begin(), 0.0);
			// Calculating the standard deviation of the numbers
			const double stdev = std::sqrt(sq_sum / numbers.size() - mean * mean);

			// Tolerances for validating the mean and standard deviation
			constexpr double mean_tolerance = 0.01;
			constexpr double stdev_tolerance = 0.01;

			// Asserting that the mean and standard deviation are within expected tolerances
			Assert::IsTrue(std::abs(mean) < mean_tolerance, LR"(Sample mean is not within the expected tolerance.)");
			Assert::IsTrue(std::abs(stdev - 1) < stdev_tolerance,
			               LR"(Sample standard deviation is not within the expected tolerance.)");
		}
	};
}
