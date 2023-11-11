#include "pch.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include "IncludePlot.h"

using namespace plot;

// Implementation of the generate function for creating Python scripts that utilize Matplotlib for plotting.
void python_matplotlib_generator::generate(
	const std::vector<std::pair<std::map<std::string, double>, std::string>>& datasets,
	const std::string& file_path,
	const std::string& title)
{
	std::ofstream outfile(file_path);

	// Write the necessary Python imports and initialization code for Matplotlib.
	outfile << "import matplotlib.pyplot as plt" << std::endl;
	outfile << "import matplotlib.dates as mdates" << std::endl;
	outfile << "import numpy as np" << std::endl;
	outfile << std::endl;
	outfile << "# Create a figure and axis" << std::endl;
	outfile << "plt.figure(figsize=(10, 6))" << std::endl;
	outfile << "plt.title('" << title << "')" << std::endl;
	outfile << std::endl;

	bool first_dataset = true; // Flag to indicate whether we are processing the first dataset.

	// Iterate over each dataset to plot its data.
	for (const auto& dataset : datasets)
	{
		const std::map<std::string, double>& data = dataset.first; // Extract the data for plotting.
		const std::string& label = dataset.second; // Extract the label for the dataset.

		// Write the data extraction code for the current dataset.
		outfile << "# Data for " << label << std::endl;
		outfile << "x = [mdates.datestr2num(date) for date in [";
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			outfile << "'" << it->first << "'";
			if (std::next(it) != data.end()) outfile << ", "; // Separate dates with commas.
		}
		outfile << "]]" << std::endl;

		outfile << "y = [";
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			outfile << it->second;
			if (std::next(it) != data.end()) outfile << ", "; // Separate values with commas.
		}
		outfile << "]" << std::endl;

		// Write the plotting code, adjusting line width for the first dataset.
		if (first_dataset)
		{
			// Plot the first dataset with a thicker line.
			outfile << "plt.plot(x, y, label='" << label << "', linewidth=5.0)" << std::endl;
			first_dataset = false; // Update the flag after the first dataset is plotted.
		}
		else
		{
			// Plot subsequent datasets with a thinner line.
			outfile << "plt.plot(x, y, linewidth=0.3)" << std::endl;
		}

		// Write code to format the x-axis dates.
		outfile << "plt.gcf().autofmt_xdate()" << std::endl;
		outfile << "plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))" << std::endl;
		outfile << std::endl;
	}

	// Write the code to add a legend to the plot.
	outfile << "# Add a legend" << std::endl;
	outfile << "plt.legend()" << std::endl;
	outfile << std::endl;
	// Write the code to display the plot.
	outfile << "# Display the plot" << std::endl;
	outfile << "plt.show()" << std::endl;

	outfile.close(); // Close the file stream.
}
