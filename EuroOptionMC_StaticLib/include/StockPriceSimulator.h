#pragma once

#include "IncludeRandom.h"
#include <vector>

using namespace random_generators;

namespace stochastic_methods
{
	// 'stock_price_simulator' simulates the price path of a stock using a stochastic process.
	class stock_price_simulator
	{
	public:
		stock_price_simulator(double initial_price,
		                      double r,
		                      double sigma,
		                      std::unique_ptr<random_base> generator);

		// Simulates a stock price path over time 't' divided into a number of 'intervals'.
		std::vector<double> simulate_price_path(double t, std::size_t intervals) const;

		// Resets the random number generator to its initial state.
		void random_generator_reset();

	private:
		double s0_; // Initial stock price at time 0.
		double r_; // Constant risk-free rate used in the stochastic process.
		double sigma_; // Constant volatility parameter of the stock's returns.
		std::unique_ptr<random_base> random_generator_;
		// Pointer to the random number generator for the stochastic differential equation.
	};
}
