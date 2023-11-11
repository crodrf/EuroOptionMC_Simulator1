#pragma once
#include "IFinancialCalculationStrategy.h"
#include <vector>

namespace data
{
	// Calculates the historical volatility of a stock
	class historical_volatility_calculator final : public i_financial_calculation_strategy {
	public:
		double execute(const std::vector<double>& data) const override; 
	};
}