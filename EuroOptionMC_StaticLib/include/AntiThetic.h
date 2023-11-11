#pragma once

#include "randomBase.h"
#include "RandomBaseWrapper.h"
#include "NumericArray.h"

namespace random_generators
{
	class anti_thetic final : public random_base
	{
	public:
		explicit anti_thetic(std::unique_ptr<random_base> inner_generator);
		~anti_thetic() override = default;

		std::unique_ptr<random_base> clone() const override;
		void get_uniforms(numeric_array& variates) override;
		void skip(unsigned long number_of_paths) override;
		void set_seed(unsigned long seed) override;
		void reset_dimensionality(unsigned long new_dimensionality) override;
		void reset() override;

	private:
		std::unique_ptr<random_base> inner_generator_;
		bool odd_even_;
		numeric_array next_variates_;
	};

}  