#pragma once

#include <memory>
#include "NumericArray.h"

namespace random_generators
{
	// 'random_base' serves as an abstract base class for various random number generators.
	class random_base
	{
	public:
		// Constructor to initialize the generator with a given dimensionality.
		explicit random_base(const unsigned long dimensionality)
			: dimensionality_(dimensionality)
		{
		}

		// Virtual destructor to allow for derived class destructors to be called.
		virtual ~random_base() = default;

		// Getter for the dimensionality of the random number generator.
		unsigned long get_dimensionality() const { return dimensionality_; }

		// Pure virtual function to clone the random number generator, facilitating polymorphism.
		virtual std::unique_ptr<random_base> clone() const = 0;
		// Pure virtual function to fill an array with uniform random numbers.
		virtual void get_uniforms(numeric_array& variates) = 0;
		// Pure virtual function to advance the random number generator state.
		virtual void skip(unsigned long number_of_paths) = 0;
		// Pure virtual function to set the random number generator's seed.
		virtual void set_seed(unsigned long seed) = 0;
		// Pure virtual function to reset the random number generator to its initial state.
		virtual void reset() = 0;

		// Non-virtual method to fill an array with Gaussian random numbers, based on the uniform variates.
		void get_gaussians(numeric_array& variates);
		// Method to change the dimensionality of the random number generator.
		virtual void reset_dimensionality(const unsigned long new_dimensionality)
		{
			dimensionality_ = new_dimensionality;
		}

	private:
		// The number of dimensions the random number generator works in.
		unsigned long dimensionality_;
	};
}
