#include "pch.h"
#include "EuropeanOptionMC.h"

#include <valarray>

namespace stochastic_methods
{
	// Constructor for the European option Monte Carlo simulation.
	// Takes ownership of the vanilla_option, volatility, risk-free rate parameters, and a random number generator.
	european_option_mc::european_option_mc(std::unique_ptr<vanilla_option> vanilla_option, parameters vol,
	                                       parameters r, std::unique_ptr<random_base> generator)
		: vanilla_option_(std::move(vanilla_option)), vol_(std::move(vol)), r_(std::move(r)),
		  random_generator_(std::move(generator))
	{
		// Initialize the convergence table with a statistics_mean handler to track simulation results.
		auto stats_handler = std::make_unique<statistics_handler>(
			std::make_unique<statistics_mean>());
		convergence_table_ = std::make_unique<convergence_table>(std::move(stats_handler));
	}

	// Prices the European option using Monte Carlo simulation over a specified number of paths.
	void european_option_mc::price(const double spot, const std::size_t n_paths) const
	{
		// Retrieve the time to expiry for the option.
		const double expiry = vanilla_option_->get_expiry();
		// Calculate the variance of the option's lognormal distribution up to expiry.
		const double variance = vol_.integral_square(0, expiry);
		// Derive the standard deviation from the variance.
		const double root_variance = std::sqrt(variance);
		// Apply Ito's correction to adjust for the drift.
		const double ito_correction = -0.5 * variance;

		// Calculate the adjusted spot price factoring in the drift and correction.
		const double moved_spot = spot * std::exp((r_.integral(0, expiry) + ito_correction));

		// Initialize a numeric array to store random gaussian values.
		numeric_array this_gaussian(1);
		// Initialize a vector to store the simulated spot price at expiry.
		std::vector<double> this_spot(1);

		// Run the simulation for the specified number of paths.
		for (std::size_t i = 0; i < n_paths; i++)
		{
			// Get a random gaussian value from the random number generator.
			random_generator_->get_gaussians(this_gaussian);

			// Calculate the simulated spot price at expiry using the random gaussian.
			this_spot[0] = (moved_spot * std::exp(root_variance * this_gaussian[0]));

			// Calculate the option payoff at expiry.
			double this_payoff = vanilla_option_->option_payoff(this_spot[0]);

			// Discount the payoff to the present value.
			this_payoff *= std::exp(-r_.integral(0, expiry));

			// Store the result in the convergence table.
			convergence_table_->dump_one_result(this_payoff);
		}
	}

	// Retrieves the results of the simulation so far from the convergence table.
	std::vector<std::vector<double>> european_option_mc::get_results_so_far() const
	{
		return convergence_table_->get_results_so_far();
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
