#pragma once
#include <map>
#include <string>
#include <vector>

namespace plot
{
	// 'i_plot_script_generator' defines an interface for generating plot scripts compatible with different plotting tools.
	class i_plot_script_generator
	{
	public:
		// Virtual destructor to allow derived classes to clean up resources.
		virtual ~i_plot_script_generator() = default;

		// Pure virtual function to generate a plot script from given datasets.
		// 'datasets' is a vector of pairs, each containing a map of string keys to double values, and a string label.
		// 'file_path' is the output path for the generated script.
		// 'title' is the desired title for the plot.
		virtual void generate(const std::vector<std::pair<std::map<std::string, double>, std::string>>& datasets,
			const std::string& file_path, const std::string& title) = 0;
	};
}
