#include "pch.h"

#include "IncludeRandom.h"
#include "NumericArray.h"

namespace random_generators
{
	constexpr double one_over_root_two_pi = 0.398942280401433;

	// standard normal (Gaussian) probability density function (PDF) at a given value x
	double normal_density(const double x)
	{
		return one_over_root_two_pi * exp(-x * x / 2);
	}

	double inverse_cumulative_normal(const double u)
	{
		// Coefficients for the rational P/Q approximation for the central range (0.5, 0.92)
		static constexpr double a[4] = {
			2.50662823884,
			-18.61500062529,
			41.39119773534,
			-25.44106049637
		};

		static constexpr double b[4] = {
			-8.47351093090,
			23.08336743743,
			-21.06224101826,
			3.13082909833
		};

		// Coefficients for the tail approximation (beyond 0.92)
		static constexpr double c[9] = {
			0.3374754822726147,
			0.9761690190917186,
			0.1607979714918209,
			0.0276438810333863,
			0.0038405729373609,
			0.0003951896511919,
			0.0000321767881768,
			0.0000002888167364,
			0.0000003960315187
		};

		// Centering the input around 0.5
		const double x = u - 0.5;
		double r;

		// For values close to median (0.5), use P/Q approximation
		if (fabs(x) < 0.42)
		{
			const double y = x * x;
			r = x * (((a[3] * y + a[2]) * y + a[1]) * y + a[0]) /
				((((b[3] * y + b[2]) * y + b[1]) * y + b[0]) * y + 1.0);
		}
		else // For tail values
		{
			// If x > 0, adjust for tail computation
			if (x > 0)
			{
				r = 1 - u;
			}
			else
			{
				r = u;
			}

			// Apply tail approximation
			r = log(-log(r));
			r = c[0] + r * (c[1] + r * (c[2] + r * (c[3] + r * (c[4] + r * (c[5] + r * (c[6] + r
				* (c[7] + r * c[8])))))));

			// Adjust the sign if x < 0
			if (x < 0)
			{
				r = -r;
			}
		}

		return r;
	}

	double cumulative_normal(double x)
	{
		// Coefficients for the Beasley-Springer/Moro approximation
		static const double a[5] = {0.319381530, -0.356563782, 1.781477937, -1.821255978, 1.330274429};

		// Constant value used in the approximation
		static const double p = 0.2316419;

		// If x is too far on the left, use tail approximation
		if (x < -7.0)
		{
			return normal_density(x) / sqrt(1. + x * x);
		}
		// If x is too far on the right, reflect and use left tail
		else if (x > 7.0)
		{
			return 1.0 - cumulative_normal(-x);
		}
		// For values of x close to 0, use the Beasley-Springer/Moro approximation
		else
		{
			const double t = 1.0 / (1.0 + p * fabs(x));

			// Compute the Beasley-Springer/Moro approximation
			const double approximation = t * (a[0] + t * (a[1] + t * (a[2] + t * (a[3] + t * a[4]))));
			double result = 1.0 - normal_density(x) * approximation;

			// Reflect the result if x is negative
			if (x <= 0.0)
			{
				result = 1.0 - result;
			}

			return result;
		}
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
