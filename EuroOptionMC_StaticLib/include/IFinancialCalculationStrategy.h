#pragma once
#include <vector>

namespace data
{
	// Interface for financial calculation strategies 
	class i_financial_calculation_strategy
	{
	public:
		virtual double execute(const std::vector<double>& data) const = 0;
		virtual ~i_financial_calculation_strategy() = default;
	};
}
