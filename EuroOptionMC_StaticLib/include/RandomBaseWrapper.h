#pragma once

#include <memory>
#include "NumericArray.h"
#include "randomBase.h"

namespace random_generators
{
	class random_base_wrapper
	{
	public:
		explicit random_base_wrapper(std::unique_ptr<random_base> random_base_ptr);

		// Delegated member functions
		unsigned long get_dimensionality() const;
		std::unique_ptr<random_base> clone() const;
		void get_uniforms(numeric_array& variates) const;
		void skip(unsigned long number_of_paths) const;
		void set_seed(unsigned long seed) const;
		void reset() const;
		void get_gaussians(numeric_array& variates);
		void reset_dimensionality(unsigned long new_dimensionality) const;

	private:
		std::unique_ptr<random_base> random_base_ptr_;
	};

	inline random_base_wrapper::random_base_wrapper(std::unique_ptr<random_base> random_base_ptr)
		: random_base_ptr_(std::move(random_base_ptr))
	{
	}

	inline unsigned long random_base_wrapper::get_dimensionality() const
	{
		return random_base_ptr_->get_dimensionality();
	}

	inline std::unique_ptr<random_base> random_base_wrapper::clone() const { return random_base_ptr_->clone(); }

	inline void random_base_wrapper::get_uniforms(numeric_array& variates) const
	{
		random_base_ptr_->get_uniforms(variates);
	}

	inline void random_base_wrapper::skip(unsigned long number_of_paths) const
	{
		random_base_ptr_->skip(number_of_paths);
	}

	inline void random_base_wrapper::set_seed(unsigned long seed) const { random_base_ptr_->set_seed(seed); }
	inline void random_base_wrapper::reset() const { random_base_ptr_->reset(); }

	inline void random_base_wrapper::get_gaussians(numeric_array& variates)
	{
		random_base_ptr_->get_gaussians(variates);
	}

	inline void random_base_wrapper::reset_dimensionality(const unsigned long new_dimensionality) const
	{
		random_base_ptr_->reset_dimensionality(new_dimensionality);
	}
}
