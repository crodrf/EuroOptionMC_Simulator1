#pragma once
#include "IFinancialCalculationStrategy.h"
#include <vector>

namespace data
{
	// Calculates the historical mean return of a given data set
	class historical_mean_return_calculator final : public i_financial_calculation_strategy {
	public:
		double execute(const std::vector<double>& data) const override;
	};
}