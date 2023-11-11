#include "pch.h"
#include "FinancialDataAnalyzer.h"

namespace data
{
	financial_data_analyzer::financial_data_analyzer(std::unique_ptr<i_financial_calculation_strategy> strategy)
		: strategy_(std::move(strategy))
	{
	}

	// Analyzes the provided financial data using the strategy pattern and returns the result.
	double financial_data_analyzer::analyze_data(const std::vector<double>& data) const
	{
		return strategy_->execute(data); // Executes the strategy's calculation method.
	}
}
