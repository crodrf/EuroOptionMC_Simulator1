#pragma once

#include "IncludeRandom.h"
#include "IncludePayoff.h"
#include "IncludeStochasticMethods.h"

#include <memory>

using namespace payoff;

namespace stochastic_methods
{
	// 'european_option_mc' performs Monte Carlo simulations to price European options.
	class european_option_mc
	{
	public:
		european_option_mc(std::unique_ptr<vanilla_option> vanilla_option, parameters vol,
		                   parameters r, std::unique_ptr<random_base> generator);

		// Method to calculate the price of the option using Monte Carlo simulation.
		// 'spot' represents the current spot price of the underlying asset.
		// 'n_paths' represents the number of simulation paths to use in the Monte Carlo simulation.
		void price(double spot, std::size_t n_paths) const;

		// Retrieves the results of the simulation so far.
		// Returns a vector of vectors, each containing price estimates at different stages of convergence.
		std::vector<std::vector<double>> get_results_so_far() const;

	private:
		// Holds the vanilla option for which the price is being simulated.
		std::unique_ptr<vanilla_option> vanilla_option_;
		// The volatility parameter object used in the simulation.
		parameters vol_;
		// The risk-free rate parameter object used in the simulation.
		parameters r_;
		// The random number generator used for path generation in the simulation.
		std::unique_ptr<random_base> random_generator_;
		// A table to store and manage the convergence data of the simulation.
		std::unique_ptr<convergence_table> convergence_table_;
	};
}
