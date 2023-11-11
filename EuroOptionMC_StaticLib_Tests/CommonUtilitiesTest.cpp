#include "pch.h"

#include "CommonUtilities.h"
#include "CppUnitTest.h"
#include "DataFilterInclude.h"
#include "TimeInterval.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data;

namespace unit_test1
{
	// Test class for common utility functions.
	TEST_CLASS(CommonUtilities)
	{
	public:
		// Test method to verify the computation of expiry time between two dates.
		TEST_METHOD(TestComputeExpiryTime)
		{
			// Define the start and end dates for the test.
			const std::string start_date = "2020-01-01";
			const std::string end_date = "2021-01-01";
			// Set the expected result for one year's expiry time.
			constexpr double expected = 1.0;
			// Compute the actual expiry time using the utility function.
			const double actual = compute_expiry_time(start_date, end_date);
			// Verify that the computed expiry time is within an acceptable tolerance of the expected result.
			Assert::AreEqual(expected, actual, 0.005);
		}

		// Test method to verify the generation of dates between two given dates.
		TEST_METHOD(TestGenerateDates)
		{
			// Define the initial and final dates for the test.
			const std::string initial_date = "2020-01-01";
			const std::string final_date = "2020-01-03";
			// Define the number of intervals for date generation.
			constexpr std::size_t intervals = 2;
			// Set the expected vector of dates.
			const std::vector<std::string> expected = {"2020-01-01", "2020-01-02", "2020-01-03"};
			// Generate the actual vector of dates using the utility function.
			const std::vector<std::string> actual = generate_dates(initial_date, final_date, intervals);
			// Verify that the generated dates match the expected dates.
			Assert::IsTrue(expected == actual);
		}
	};
}
