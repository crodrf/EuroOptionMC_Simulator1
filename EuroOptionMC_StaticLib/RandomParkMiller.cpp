#include "pch.h"

#include "ParkMiller.h"
#include "RandomParkMiller.h"

namespace random_generators
{
	// Initializes the base class with the dimensionality and sets up the Park-Miller generator with the provided seed.
	random_park_miller::random_park_miller(const unsigned long dimensionality, const unsigned long seed)
		: random_base(dimensionality), // Initialize the base class part of this object.
		  inner_generator_(seed), // Initialize the inner Park-Miller generator with the given seed.
		  initial_seed_(seed), // Store the initial seed.
		  reciprocal_(1.0 / (1.0 + inner_generator_.max()))
	// Precompute the reciprocal for uniform distribution conversion.
	{
	}

	// Creates a copy of this random_park_miller object.
	std::unique_ptr<random_base> random_park_miller::clone() const
	{
		return std::make_unique<random_park_miller>(*this);
	}

	// Fills the provided numeric_array with uniformly distributed random numbers.
	void random_park_miller::get_uniforms(numeric_array& variates)
	{
		for (unsigned long j = 0; j < get_dimensionality(); j++)
		{
			variates[j] = inner_generator_.get_one_random_integer() * reciprocal_; // Convert to a uniform distribution.
		}
	}

	// Skips a number of paths in the random number sequence.
	void random_park_miller::skip(const unsigned long number_of_paths)
	{
		numeric_array tmp(get_dimensionality());
		for (unsigned long j = 0; j < number_of_paths; j++)
		{
			get_uniforms(tmp); // Advance the sequence by getting uniforms without storing them.
		}
	}

	// Sets a new seed for the random number generator.
	void random_park_miller::set_seed(const unsigned long seed)
	{
		initial_seed_ = seed; // Store the new seed.
		inner_generator_.set_seed(seed); // Reset the inner generator with the new seed.
	}

	// Resets the random number generator to its initial state using the initial seed.
	void random_park_miller::reset()
	{
		inner_generator_.set_seed(initial_seed_); // Reset the inner generator using the initial seed.
	}

	// Resets the dimensionality of the random number generator and reinitializes it.
	void random_park_miller::reset_dimensionality(const unsigned long new_dimensionality)
	{
		random_base::reset_dimensionality(new_dimensionality); // Reset the base class dimensionality.
		inner_generator_.set_seed(initial_seed_); // Reinitialize the inner generator with the initial seed.
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
