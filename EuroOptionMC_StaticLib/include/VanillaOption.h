#pragma once

#include <memory>
#include "Payoff.h"

namespace payoff
{
	// The 'vanilla_option' class represents a standard or "vanilla" financial option.
	class vanilla_option
	{
		std::unique_ptr<i_payoff> payoff_;

		double expiry_; // Expiry time of the option. This is the time in years until the option expires.

	public:
		vanilla_option(std::unique_ptr<i_payoff> payoff, double expiry);

		double option_payoff(double spot_price) const;
		// Calculate and return the payoff of the option given the current spot price of the underlying asset.

		double get_expiry() const;
	};
}
