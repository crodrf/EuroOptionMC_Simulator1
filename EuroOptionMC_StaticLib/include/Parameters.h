#pragma once
#include <memory>

#include "ParameterInner.h"


namespace stochastic_methods
{
	class parameters
	{
	public:
		explicit parameters(std::unique_ptr<parameter_inner> inner_object);

		parameters(const parameters& other);
		parameters(parameters&& other) noexcept;
		parameters& operator=(parameters other);

		// Delegates the integral calculation to the encapsulated 'parameter_inner' object.
		double integral(double time1, double time2) const;

		// Delegates the calculation of the integral of the square to the 'parameter_inner' object.
		double integral_square(double time1, double time2) const;

		// Calculates the mean of the parameter over a given time interval.
		double mean(double time1, double time2) const;

		// Calculates the root mean square of the parameter over a given time interval.
		double root_mean_square(double time1, double time2) const;

		// Non-member swap function to allow the swap of two 'parameters' objects.
		friend void swap(parameters& a, parameters& b) noexcept;

	private:
		// Smart pointer to the 'parameter_inner' object which performs the actual calculations.
		std::unique_ptr<parameter_inner> inner_object_;
	};
}
