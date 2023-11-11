#include "pch.h"
#include "RiskFreeRateCalculator.h"

#include <iostream>
#include <numeric>

namespace data
{
	// Executes the calculation of the risk-free rate given a vector of risk-free rate data points.
	double risk_free_rate_calculator::execute(const std::vector<double>& data) const
	{
		// Check if the data vector is empty and return 0.0 since calculation cannot proceed.
		if (data.empty())
		{
			std::cerr << "Error: Data vector is empty for RiskFreeRateCalculator." << std::endl;
			return 0.0;
		}

		// Sum all the values in the data vector.
		const double sum = std::accumulate(data.begin(), data.end(), 0.0);

		// Calculate the average of the data points to represent the risk-free rate.
		return sum / static_cast<double>(data.size());
	}
}
