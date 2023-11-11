#include "pch.h"
#include "NumericArray.h"

#include <algorithm>
#include <numeric>
#include <stdexcept>


numeric_array& numeric_array::operator+=(const numeric_array& operand)
{
	if (values_.size() != operand.values_.size())
	{
		throw std::runtime_error("Sizes of the arrays do not match.");
	}

	for (size_t i = 0; i < values_.size(); ++i)
	{
		values_[i] += operand.values_[i];
	}

	return *this;
}

numeric_array& numeric_array::operator-=(const numeric_array& operand)
{
	if (values_.size() != operand.values_.size())
	{
		throw std::runtime_error("Sizes of the arrays do not match.");
	}

	for (size_t i = 0; i < values_.size(); ++i)
	{
		values_[i] -= operand.values_[i];
	}

	return *this;
}

numeric_array& numeric_array::operator/=(const double operand)
{
	if (operand == 0.0)
	{
		throw std::runtime_error("Division by zero.");
	}

	for (double& value : values_)
	{
		value /= operand;
	}

	return *this;
}

numeric_array& numeric_array::operator*=(double operand)
{
	for (double& value : values_)
	{
		value *= operand;
	}

	return *this;
}

double numeric_array::sum() const
{
	return std::accumulate(values_.begin(), values_.end(), 0.0);
}

double numeric_array::min() const
{
	return *std::min_element(values_.begin(), values_.end());
}

double numeric_array::max() const
{
	return *std::max_element(values_.begin(), values_.end());
}

numeric_array operator+(const numeric_array& lhs, const numeric_array& rhs)
{
	numeric_array result = lhs;
	result += rhs;
	return result;
}

numeric_array operator-(const numeric_array& lhs, const numeric_array& rhs)
{
	numeric_array result = lhs;
	result -= rhs;
	return result;
}

numeric_array operator*(const numeric_array& lhs, const double rhs)
{
	numeric_array result = lhs;
	result *= rhs;
	return result;
}

numeric_array operator*(const double lhs, const numeric_array& rhs)
{
	return rhs * lhs;
}

numeric_array operator/(const numeric_array& lhs, const double rhs)
{
	numeric_array result = lhs;
	result /= rhs;
	return result;
}
