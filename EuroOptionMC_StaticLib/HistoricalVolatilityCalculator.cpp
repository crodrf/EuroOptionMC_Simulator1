#include "pch.h"
#include "HistoricalVolatilityCalculator.h"

#include <cmath>
#include <iostream>
#include <numeric>

namespace data
{
	// Calculates the historical volatility of a given dataset.
	double historical_volatility_calculator::execute(const std::vector<double>& data) const
	{
		// Ensure there is enough data to calculate volatility.
		if (data.size() < 2)
		{
			std::cerr << "Error: Insufficient data for HistoricalVolatilityCalculator." << std::endl;
			return 0.0; // Cannot calculate volatility without sufficient data.
		}

		// Vector to store the logarithmic returns of the data.
		std::vector<double> log_returns;

		// Compute the logarithmic returns for each data point.
		for (std::size_t i = 1; i < data.size(); ++i)
		{
			log_returns.push_back(std::log(data[i] / data[i - 1]));
		}

		// Calculate the mean of the log returns.
		const double mean = std::accumulate(log_returns.begin(), log_returns.end(), 0.0) / log_returns.size();

		// Compute the sum of squares of the log returns.
		const double sq_sum = std::inner_product(log_returns.begin(), log_returns.end(), log_returns.begin(), 0.0);

		// Calculate the variance of the log returns.
		const double variance = sq_sum / static_cast<double>(log_returns.size()) - mean * mean;

		// Annualize the volatility by multiplying the standard deviation by the square root of the number of trading days in a year.
		const double annualized_volatility = std::sqrt(variance) * std::sqrt(252);

		// Return the annualized historical volatility.
		return annualized_volatility;
	}
}
