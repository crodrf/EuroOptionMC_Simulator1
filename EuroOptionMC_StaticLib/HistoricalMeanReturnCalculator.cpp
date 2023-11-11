#include "pch.h"
#include "HistoricalMeanReturnCalculator.h"

#include <cmath>
#include <iostream>
#include <numeric>

namespace data
{
	// Executes the calculation of the historical mean return given a vector of price data.
	double historical_mean_return_calculator::execute(const std::vector<double>& data) const
	{
		// Check if there's sufficient data to calculate mean return.
		if (data.size() < 2)
		{
			// Print an error message if data is insufficient.
			std::cerr << "Error: Insufficient data for HistoricalMeanReturnCalculator." << std::endl;
			return 0.0; // Return 0 as we cannot calculate mean on insufficient data.
		}

		// Vector to store the calculated logarithmic returns.
		std::vector<double> log_returns;

		// Calculate the logarithmic returns of consecutive prices.
		for (std::size_t i = 1; i < data.size(); ++i)
		{
			// Calculate log return and add it to the log_returns vector.
			log_returns.push_back(std::log(data[i] / data[i - 1]));
		}

		// Calculate the mean of the log returns.
		const double daily_mean = std::accumulate(log_returns.begin(), log_returns.end(), 0.0) / static_cast<double>(
			log_returns.size());

		// Annualize the mean by multiplying by the number of trading days in a year (usually 252).
		const double annualized_mean = daily_mean * 252;

		// Return the annualized mean return.
		return annualized_mean;
	}
}
