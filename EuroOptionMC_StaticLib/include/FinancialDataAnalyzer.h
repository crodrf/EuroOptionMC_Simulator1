#pragma once
#include <memory>
#include <vector>

#include "IFinancialCalculationStrategy.h"

namespace data
{
	// The 'financial_data_analyzer' acts as a context in the Strategy pattern, which
	// delegates the data analysis to a strategy object implementing the 'i_financial_calculation_strategy'.
	class financial_data_analyzer
	{
	public:
		explicit financial_data_analyzer(std::unique_ptr<i_financial_calculation_strategy> strategy);

		double analyze_data(const std::vector<double>& data) const;
		// Method to analyze the data using the strategy and return a numerical result.

	private:
		std::unique_ptr<i_financial_calculation_strategy> strategy_;
		// The strategy object that is used for performing the calculation.
	};
}
