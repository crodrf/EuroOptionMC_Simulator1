#pragma once

#include <memory>
#include "NumericArray.h"
#include "IncludeRandom.h"

// Namespace for random number generator utility functions.
namespace random_generators
{
	// Computes the value of the probability density function of the standard normal distribution at a given point x.
	double normal_density(double x);

	// Calculates the inverse of the cumulative distribution function of the standard normal distribution for a given probability u.
	double inverse_cumulative_normal(double u);

	// Calculates the cumulative distribution function of the standard normal distribution for a given value x.
	double cumulative_normal(double x);
}
