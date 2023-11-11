#include "pch.h" 

#include <CppUnitTest.h> 
#include <memory> 

#include "ConvergenceTable.h" 
#include "IncludeParameter.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace stochastic_methods;

namespace parameters
{
	// Test class for the parameters functionality.
	TEST_CLASS(ParameterTests)
	{
	public:
		// Test method to verify the integral computation of parameters.
		TEST_METHOD(integrateParameters)
		{
			double constant = 1.0;
			// Create a unique_ptr to a new parameters_constant object initialized with the constant.
			std::unique_ptr<parameter_inner> parameter_inner = std::make_unique<parameters_constant>(constant);
			// Construct a parameters object using the parameters_constant object.
			const stochastic_methods::parameters parameter(std::move(parameter_inner));
			// Define the time interval for the integral computation.
			constexpr double t1 = 0.0;
			constexpr double t2 = 2.0;
			// Perform the integral computation over the given time interval.
			const double result = parameter.integral(t1, t2);
			// Define the expected result for the integral of a constant over the interval [t1, t2].
			constexpr double expected = 2.0;
			// Set the tolerance for floating point comparison.
			constexpr double tolerance = 1e-6;
			// Assert that the computed result matches the expected result within the specified tolerance.
			Assert::AreEqual(expected, result, tolerance, L"Failed to compute the integral");
		}

		// Test method to verify the computation of mean of parameters.
		TEST_METHOD(meanParameters)
		{
			double constant = 1.0; // The constant value for the parameters_constant object.
			// Create a unique_ptr to a new parameters_constant object initialized with the constant.
			std::unique_ptr<parameter_inner> parameter_inner = std::make_unique<parameters_constant>(constant);
			// Construct a parameters object using the parameters_constant object.
			const stochastic_methods::parameters parameter(std::move(parameter_inner));
			// Define the time interval for the mean computation.
			constexpr double t1 = 0.0;
			constexpr double t2 = 2.0;
			// Perform the mean computation over the given time interval.
			const double result = parameter.mean(t1, t2);
			// Define the expected result for the mean of a constant over the interval [t1, t2].
			constexpr double expected = 1.0;
			// Set the tolerance for floating point comparison.
			constexpr double tolerance = 1e-6;
			// Assert that the computed result matches the expected result within the specified tolerance.
			Assert::AreEqual(expected, result, tolerance, L"Failed to compute the mean");
		}
	};
}
