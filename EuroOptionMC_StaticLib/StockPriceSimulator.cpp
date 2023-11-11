#include "pch.h"
#include "StockPriceSimulator.h"
#include "NumericArray.h"

#include <cmath>

using namespace random_generators;

namespace stochastic_methods
{
	// Constructor for stock price simulator. Initializes with starting price, risk-free rate, volatility, and random number generator.
	stock_price_simulator::stock_price_simulator(const double initial_price,
	                                             const double r,
	                                             const double sigma,
	                                             std::unique_ptr<random_base> generator)
		: s0_(initial_price), r_(r), sigma_(sigma), random_generator_(std::move(generator))
	{
	}

	// Simulate the stock price path over time T with a specified number of intervals.
	std::vector<double> stock_price_simulator::simulate_price_path(double T, const std::size_t intervals) const
	{
		std::vector<double> price_path; // Vector to store the simulated price path.
		const double dt = T / static_cast<double>(intervals); // Time step for each interval.
		double current_price = s0_; // Initialize current price to the initial stock price.
		price_path.reserve(intervals + 1); // Reserve space to avoid reallocations.
		price_path.push_back(current_price); // Add initial price to the path.

		// Pre-calculate the drift component of the price.
		const double drift = r_ * current_price * dt;

		// Iterate over each time step to simulate the price path.
		for (std::size_t i = 1; i <= intervals; ++i)
		{
			numeric_array this_gaussian(1); // Array to store Gaussian random numbers.
			random_generator_->get_gaussians(this_gaussian); // Populate array with random numbers.
			// Calculate the diffusion component with the current price, volatility, and random number.
			const double diffusion = sigma_ * current_price * this_gaussian[0] * std::sqrt(dt);
			// Update the current price with both the drift and diffusion.
			current_price += drift + diffusion;
			// Add the updated price to the path.
			price_path.push_back(current_price);
		}

		return price_path; // Return the complete price path.
	}

	// Reset the random number generator to its initial state for reproducibility.
	void stock_price_simulator::random_generator_reset()
	{
		random_generator_->reset();
	}
}
