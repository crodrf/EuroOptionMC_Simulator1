#pragma once

#include <memory>
#include <vector>

#include "StatisticsMC.h"

namespace stochastic_methods
{
	// 'statistics_mean' is a concrete class that calculates the running mean of simulation results.
	class statistics_mean final : public statistics_mc
	{
	public:
		statistics_mean() = default;

		statistics_mean(const statistics_mean& other) = default;

		statistics_mean& operator=(const statistics_mean& other) = default;

		statistics_mean(statistics_mean&& other) noexcept = default;

		statistics_mean& operator=(statistics_mean&& other) noexcept = default;

		void dump_one_result(double result) override;

		std::vector<std::vector<double>> get_results_so_far() const override;

		std::unique_ptr<statistics_mc> clone() const override;

	private:
		// Sum of all results received, used to compute the running mean.
		double running_sum_ = 0.0;

		// Count of how many results (paths) have been processed.
		int paths_done_ = 0;
	};
}
