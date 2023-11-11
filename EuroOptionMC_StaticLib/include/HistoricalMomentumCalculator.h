#pragma once
#include "IFinancialCalculationStrategy.h"
#include <vector>

namespace data
{
	class HistoricalMomentumCalculator: public IFinancialCalculationStrategy {
	public:
		double execute(const std::vector<double>& data) const override;
	};
}