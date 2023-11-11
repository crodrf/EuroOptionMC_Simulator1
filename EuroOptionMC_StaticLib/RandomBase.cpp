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
