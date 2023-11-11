#include "pch.h"

#include "IncludeRandom.h"
#include "NumericArray.h"

namespace random_generators
{
	// Fills the numeric array with Gaussian-distributed random numbers using the inverse transform method.
	void random_base::get_gaussians(numeric_array& variates)
	{
		get_uniforms(variates); // First, fill the array with uniformly distributed numbers.

		// Transform the uniform variates to Gaussian variates using the inverse cumulative normal function.
		for (unsigned long i = 0; i < dimensionality_; i++)
		{
			variates[i] = inverse_cumulative_normal(variates[i]);
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
