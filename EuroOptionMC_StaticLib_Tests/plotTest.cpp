// Include the precompiled header for efficiency
#include "pch.h"

#include <map>
#include <memory>
#include <vector>

#include "CommonUtilities.h"
#include "CppUnitTest.h"
#include "IncludePlot.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace plot
{
	TEST_CLASS(test_plot)
	{
	public:
		// Test method to verify line plotting
		TEST_METHOD(plotting_lines)
		{
			// Example vector to store pairs of data maps and their corresponding labels
			std::vector<std::pair<std::map<std::string, double>, std::string>> example;

			// Two vectors representing y-values for the two lines to be plotted
			const std::vector<double> a = { 1, 2, 3, 4 };
			const std::vector<double> b = { 1.5, 5, 7, 4.5 };

			// Define start and end dates for the x-axis labels
			const std::string stock_start_date = "2020-01-01";
			const std::string stock_end_date = "2021-01-01";

			// Generate dates for the x-axis based on the given start and end dates and the number of points
			const std::vector<std::string> dates = generate_dates(stock_start_date, stock_end_date, 4);

			// First map to associate dates with the first set of y-values
			std::map<std::string, double> map1;
			for (int i = 0; i < a.size(); i++)
			{
				map1[dates[i]] = a[i];
			}

			// Pair the first map with a label and add to the example vector
			const std::pair<std::map<std::string, double>, std::string> line1{map1, "line1"};
			example.push_back(line1);

			// Second map to associate dates with the second set of y-values
			std::map<std::string, double> map2;
			for (int i = 0; i < a.size(); i++)
			{
				map2[dates[i]] = b[i];
			}

			// Pair the second map with a label and add to the example vector
			const std::pair<std::map<std::string, double>, std::string> line2{map2, "line2"};
			example.push_back(line2);

			// Create an instance of the plot script generator
			std::unique_ptr<i_plot_script_generator> plot_script_generator = std::make_unique<
				python_matplotlib_generator>();

			// Define file path and title for the plot script
			std::string file_path = "plot_test.py";
			std::string title = "plot_test";

			// Generate the plot script with the given data, file path, and title
			plot_script_generator->generate(example, file_path, title);

			// Uncomment the line below to execute the generated Python script for plotting
			//system("python plot_test.py");
		}
	};
}
