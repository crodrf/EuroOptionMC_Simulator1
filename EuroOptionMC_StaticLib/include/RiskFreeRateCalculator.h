#pragma once
#include "IFinancialCalculationStrategy.h"
#include <vector>

namespace data
{
	// Calculates the risk free rate of return
	class risk_free_rate_calculator final : public i_financial_calculation_strategy
	{
	public:
		double execute(const std::vector<double>& data) const override;
	};
}
