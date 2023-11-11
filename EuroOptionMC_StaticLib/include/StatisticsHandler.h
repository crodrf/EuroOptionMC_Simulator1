#pragma once

#include "StatisticsMC.h"
#include <vector>

namespace stochastic_methods
{
	// 'statistics_handler' manages a statistics object for Monte Carlo simulations.
	class statistics_handler
	{
	public:
		statistics_handler() = default;

		explicit statistics_handler(std::unique_ptr<statistics_mc> other) : stats_object_(std::move(other))
		{
		}

		statistics_handler(const statistics_handler& other);

		statistics_handler& operator=(const statistics_handler& other);

		statistics_handler(statistics_handler&& other) noexcept;

		statistics_handler& operator=(statistics_handler&& other) noexcept;

		// Dumps a single result from a Monte Carlo simulation to the encapsulated statistics object.
		void dump_one_result(double result) const;

		// Retrieves the results accumulated so far from the encapsulated statistics object.
		std::vector<std::vector<double>> get_results_so_far() const;

		// Clones the encapsulated 'statistics_mc' object.
		std::unique_ptr<statistics_mc> clone() const;

	private:
		// Unique pointer to the encapsulated 'statistics_mc' object that performs the actual statistical calculations.
		std::unique_ptr<statistics_mc> stats_object_;
	};
}
