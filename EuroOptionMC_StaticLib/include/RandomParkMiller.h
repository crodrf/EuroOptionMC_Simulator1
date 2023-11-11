#pragma once

#include "randomBase.h"
#include "NumericArray.h"
#include "ParkMiller.h"

namespace random_generators
{
	// 'random_park_miller' extends 'random_base' to provide Park-Miller based random number generation.
	class random_park_miller final : public random_base
	{
	public:
		// Constructor with specified dimensionality and optional seed, defaults to 1 if not provided.
		explicit random_park_miller(unsigned long dimensionality, unsigned long seed = 1);

		// Creates a new instance of 'random_park_miller' that is a copy of the current instance.
		std::unique_ptr<random_base> clone() const override;
		// Generates a sequence of uniformly distributed random numbers.
		void get_uniforms(numeric_array& variates) override;
		// Skips a specified number of random number paths.
		void skip(unsigned long number_of_paths) override;
		// Sets a new seed for the random number generator.
		void set_seed(unsigned long seed) override;
		// Resets the random number generator to its initial state.
		void reset() override;
		// Resets the generator's dimensionality to a new value.
		void reset_dimensionality(unsigned long new_dimensionality) override;

	private:
		park_miller inner_generator_; // Encapsulated Park-Miller generator.
		unsigned long initial_seed_; // The initial seed provided upon construction.
		double reciprocal_; // Precomputed reciprocal for converting integers to uniform random numbers.
	};
}
