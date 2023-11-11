#pragma once

#include <vector>
#include <memory>

namespace stochastic_methods
{
	// Abstract base class for collecting statistics from Monte Carlo simulations.
	class statistics_mc
	{
	public:
		virtual ~statistics_mc() = default;

		// Pure virtual function that takes a single simulation result and updates the statistics accordingly.
		virtual void dump_one_result(double result) = 0;

		// Pure virtual function that returns a vector of vectors containing the collected simulation results so far.
		virtual std::vector<std::vector<double>> get_results_so_far() const = 0;

		// Pure virtual function that creates a copy of the statistics object, supporting polymorphic copying.
		virtual std::unique_ptr<statistics_mc> clone() const = 0;
	};
}
