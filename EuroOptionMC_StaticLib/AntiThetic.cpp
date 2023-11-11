#include "pch.h"
#include "AntiThetic.h"

#include <memory>

namespace random_generators
{
	anti_thetic::anti_thetic(std::unique_ptr<random_base> inner_generator)
		: random_base(inner_generator->get_dimensionality()),
		  inner_generator_(std::move(inner_generator)),
		  odd_even_(true)
	{
		inner_generator_->reset();
		next_variates_.resize(get_dimensionality());
	}

	std::unique_ptr<random_base> anti_thetic::clone() const
	{
		return std::make_unique<anti_thetic>(inner_generator_->clone());
	}

	void anti_thetic::set_seed(unsigned long seed)
	{
		inner_generator_->set_seed(seed);
		odd_even_ = true;
	}

	void anti_thetic::skip(unsigned long number_of_paths)
	{
		if (number_of_paths == 0) return;
		if (odd_even_)
		{
			odd_even_ = false;
			number_of_paths--;
		}
		inner_generator_->skip(number_of_paths / 2);
		if (number_of_paths % 2)
		{
			numeric_array tmp(get_dimensionality());
			get_uniforms(tmp);
		}
	}

	void anti_thetic::reset_dimensionality(unsigned long new_dimensionality)
	{
		random_base::reset_dimensionality(new_dimensionality);
		next_variates_.resize(new_dimensionality);
		inner_generator_->reset_dimensionality(new_dimensionality);
	}

	void anti_thetic::reset()
	{
		inner_generator_->reset();
		odd_even_ = true;
	}

	void anti_thetic::get_uniforms(numeric_array& variates)
	{
		if (odd_even_)
		{
			inner_generator_->get_uniforms(variates);
			for (unsigned long i = 0; i < get_dimensionality(); i++)
			{
				next_variates_[i] = 1.0 - variates[i];
			}
			odd_even_ = false;
		}
		else
		{
			variates = next_variates_;
			odd_even_ = true;
		}
	}
}
