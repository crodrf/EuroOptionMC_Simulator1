#include "pch.h"

#include <algorithm>

#include "Payoff.h"

namespace payoff
{
	// Default destructor for the abstract 'i_payoff' class.
	i_payoff::~i_payoff() = default;

	// Constructor for the 'digital_call_payoff' class initializing the strike price.
	digital_call_payoff::digital_call_payoff(const double strike_price) : strike_price_(strike_price)
	{
	}

	// Calculate payoff for a digital call option: 1 if above strike price, 0 otherwise.
	double digital_call_payoff::calculate(const double spot_price) const
	{
		return (spot_price > strike_price_) ? 1.0 : 0.0;
	}

	// Constructor for the 'digital_put_payoff' class initializing the strike price.
	digital_put_payoff::digital_put_payoff(const double strike_price) : strike_price_(strike_price)
	{
	}

	// Calculate payoff for a digital put option: 1 if below strike price, 0 otherwise.
	double digital_put_payoff::calculate(const double spot_price) const
	{
		return (spot_price < strike_price_) ? 1.0 : 0.0;
	}

	// Constructor for the 'european_call_payoff' class initializing the strike price.
	european_call_payoff::european_call_payoff(const double strike_price) : strike_price_(strike_price)
	{
	}

	// Calculate payoff for a European call option: difference between spot price and strike price if positive, 0 otherwise.
	double european_call_payoff::calculate(const double spot_price) const
	{
		return std::max(0.0, spot_price - strike_price_);
	}

	// Constructor for the 'european_put_payoff' class initializing the strike price.
	european_put_payoff::european_put_payoff(const double strike_price) : strike_price_(strike_price)
	{
	}

	// Calculate payoff for a European put option: difference between strike price and spot price if positive, 0 otherwise.
	double european_put_payoff::calculate(const double spot_price) const
	{
		return std::max(0.0, strike_price_ - spot_price);
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
