#pragma once

#include <vector>
#undef min
#undef max

	class numeric_array {
	public:
		// Constructors and destructor
		explicit numeric_array(const unsigned long size = 0) : values_(size) {}
		numeric_array(const numeric_array& original) = default;
		numeric_array(numeric_array&& original) noexcept = default;
		~numeric_array() = default;

		// Assignment operators
		numeric_array& operator=(const numeric_array& original) = default;
		numeric_array& operator=(numeric_array&& original) noexcept = default;

		// Arithmetic operations
		numeric_array& operator+=(const numeric_array& operand);
		numeric_array& operator-=(const numeric_array& operand);
		numeric_array& operator/=(double operand);
		numeric_array& operator*=(double operand);

		// Element access
		double operator[](const unsigned long i) const { return values_[i]; }
		double& operator[](const unsigned long i) { return values_[i]; }

		// Other member functions
		unsigned long size() const { return values_.size(); }
		void resize(const unsigned long new_size) { values_.resize(new_size); }
		double sum() const;
		double min() const;
		double max() const;

		//Pointers
		std::vector<double>::iterator begin() { return values_.begin(); }
		std::vector<double>::iterator end() { return values_.end(); }

	private:
		std::vector<double> values_;
	};

	// Non-member helper function prototypes
	numeric_array operator+(const numeric_array& lhs, const numeric_array& rhs);
	numeric_array operator-(const numeric_array& lhs, const numeric_array& rhs);
	numeric_array operator*(const numeric_array& lhs, double rhs);
	numeric_array operator*(double lhs, const numeric_array& rhs);
	numeric_array operator/(const numeric_array& lhs, double rhs);
