#pragma once
#include <memory>
#include "ParameterInner.h"

namespace stochastic_methods
{
	class parameters_constant final : public parameter_inner
	{
	public:
		explicit parameters_constant(double constant);

		std::unique_ptr<parameter_inner> clone() const override;

		// Calculates the integral of the constant parameter over a time interval, which is simply the constant multiplied by the time difference.
		double integral(double time1, double time2) const override;

		// Calculates the integral of the square of the constant parameter over a time interval.
		double integral_square(double time1, double time2) const override;

	private:
		double constant_; // The value of the constant parameter.
		double constant_square_; // The square of the constant parameter precalculated for efficiency.
	};
}
