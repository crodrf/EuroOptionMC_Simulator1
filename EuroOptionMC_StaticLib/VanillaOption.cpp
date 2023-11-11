#include "pch.h"
#include "VanillaOption.h"

namespace payoff
{
	// Constructor for the 'vanilla_option' class, which initializes the option with a payoff object and expiry time.
	vanilla_option::vanilla_option(std::unique_ptr<i_payoff> payoff, const double expiry)
		: payoff_(std::move(payoff)), expiry_(expiry)
	{
	}

	// Calculates and returns the payoff of the option given the current spot price.
	double vanilla_option::option_payoff(const double spot_price) const
	{
		return payoff_->calculate(spot_price);
	}

	// Returns the expiry time of the option.
	double vanilla_option::get_expiry() const
	{
		return expiry_;
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
