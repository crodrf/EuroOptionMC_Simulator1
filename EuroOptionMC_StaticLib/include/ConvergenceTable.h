#pragma once

#include <memory>
#include <vector>

#include "StatisticsHandler.h"
#include "StatisticsMC.h"

namespace stochastic_methods
{
	// 'convergence_table' extends 'statistics_mc' to track the convergence of Monte Carlo simulations.
	class convergence_table final : public statistics_mc
	{
	public:
		explicit convergence_table(std::unique_ptr<statistics_handler> inner);

		~convergence_table() override = default;

		convergence_table(const convergence_table& other);

		convergence_table& operator=(const convergence_table& other) = delete;

		convergence_table(convergence_table&& other) noexcept = default;

		convergence_table& operator=(convergence_table&& other) noexcept = default;

		std::unique_ptr<statistics_mc> clone() const override;

		void dump_one_result(double result) override; // Adds a single simulation result into the convergence tracking.

		std::vector<std::vector<double>> get_results_so_far() const override;
		// Retrieves the results accumulated so far in the convergence table.

	private:
		std::unique_ptr<statistics_handler> inner_;
		// Unique_ptr to a 'statistics_handler' that does the actual statistical calculations.

		std::vector<std::vector<double>> results_so_far_; // Matrix to store results at various stages of convergence.

		int stop_point_; // Points at which to store intermediate results.

		int paths_done_; // Counter for the number of paths simulated so far.
	};
}
