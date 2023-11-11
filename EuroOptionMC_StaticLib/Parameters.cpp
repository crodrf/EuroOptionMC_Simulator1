#include "pch.h"
#include "IncludeParameter.h"

namespace stochastic_methods
{
	parameter_inner::~parameter_inner() = default;

	parameters::parameters(std::unique_ptr<parameter_inner> inner_object) : inner_object_(std::move(inner_object))
	{
	}

	parameters::parameters(const parameters& other) : inner_object_(other.inner_object_->clone())
	{
	}

	parameters::parameters(parameters&& other) noexcept : inner_object_(std::move(other.inner_object_))
	{
	}

	parameters& parameters::operator=(parameters other)
	{
		swap(*this, other);
		return *this;
	}

	// Calculates the integral of the parameter over a given time interval.
	double parameters::integral(const double time1, const double time2) const
	{
		return inner_object_->integral(time1, time2);
	}

	// Calculates the integral of the square of the parameter over a given time interval.
	double parameters::integral_square(const double time1, const double time2) const
	{
		return inner_object_->integral_square(time1, time2);
	}

	// Calculates the mean of the parameter over a given time interval.
	double parameters::mean(const double time1, const double time2) const
	{
		return integral(time1, time2) / (time2 - time1);
	}

	// Calculates the root mean square of the parameter over a given time interval.
	double parameters::root_mean_square(const double time1, const double time2) const
	{
		return integral_square(time1, time2) / (time2 - time1);
	}

	void swap(parameters& a, parameters& b) noexcept
	{
		using std::swap;
		swap(a.inner_object_, b.inner_object_);
	}

	parameters_constant::parameters_constant(const double constant) : constant_(constant),
	                                                                  constant_square_(constant * constant)
	{
	}

	std::unique_ptr<parameter_inner> parameters_constant::clone() const
	{
		return std::make_unique<parameters_constant>(constant_);
	}

	// Calculates the integral of the constant parameter over a given time interval.
	double parameters_constant::integral(const double time1, const double time2) const
	{
		return (time2 - time1) * constant_;
	}

	// Calculates the integral of the square of the constant parameter over a given time interval.
	double parameters_constant::integral_square(const double time1, const double time2) const
	{
		return (time2 - time1) * constant_square_;
	}
}


/*
 * This portion of code is adapted from Mark Joshi's work in "C++ Design Patterns and Derivatives Pricing".
 * Copyright (c) 2002 Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
 */
