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
