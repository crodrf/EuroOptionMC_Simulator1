#pragma once
#include "IPlotScriptGenerator.h"

namespace plot
{
	// 'python_matplotlib_generator' is a concrete class that implements the 'i_plot_script_generator' interface
	// to create scripts for plotting data using Python's matplotlib library.
	class python_matplotlib_generator final : public i_plot_script_generator
	{
	public:
		// Overrides the 'generate' method from 'i_plot_script_generator' to generate a matplotlib plotting script.
		// 'datasets' contains the data to be plotted, paired with a descriptor string.
		// 'file_path' specifies where to save the generated script.
		// 'title' sets the title of the plot.
		void generate(const std::vector<std::pair<std::map<std::string, double>, std::string>>& datasets,
		              const std::string& file_path, const std::string& title) override;
	};
}
