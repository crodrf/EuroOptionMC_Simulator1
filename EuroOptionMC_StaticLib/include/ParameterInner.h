#pragma once
#include <memory> 

namespace stochastic_methods
{
	class parameter_inner
	{
	public:
		virtual ~parameter_inner();

		virtual std::unique_ptr<parameter_inner> clone() const = 0;

		// Pure virtual function to calculate the integral of the parameter over a time interval.
		virtual double integral(double time1, double time2) const = 0;

		// Pure virtual function to calculate the integral of the square of the parameter over a time interval.
		virtual double integral_square(double time1, double time2) const = 0;
	};
}
