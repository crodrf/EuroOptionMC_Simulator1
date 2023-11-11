#include "pch.h"

#include "CppUnitTest.h"
#include "StockPriceSimulator.h"
#include "DataFilterInclude.h"
#include "IncludePlot.h"

#include <cstdlib>
#include <filesystem>
#include <TimeInterval.h>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace stochastic_methods;
using namespace data;
using namespace plot;

namespace unit_test1
{
	// Test class for data related operations
	TEST_CLASS(DataNamespaceTests)
	{
	public:
		// Test method to compare plots for data analysis
		TEST_METHOD(compare_plots)
		{
			// Container to store final results for plotting
			std::vector<std::pair<std::map<std::string, double>, std::string>> final_results;

			// Stock information and date range
			const std::string stock_start_date = "2020-01-01";
			const std::string stock_end_date = "2021-01-01";
			const std::string stock_ticker = "AAPL";

			// Constructing URL to fetch stock data
			const auto stock_url = construct_url(stock_ticker, stock_start_date, stock_end_date);
			// Creating a data collector object for the stock
			const std::unique_ptr<financial_data_collector> data_collector = std::make_unique<financial_data_collector>(
				stock_url, stock_ticker);

			// Fetching the stock data
			const bool fetch_data_success = data_collector->fetch_data();
			// Asserting successful data fetching
			Assert::IsTrue(fetch_data_success, L"Failed to fetch stock data!");

			// Retrieving the fetched stock price data
			const auto stock_data = data_collector->get_price_data();
			// Mapping dates to stock prices
			const auto map_data = data_collector->get_date_to_price_map();

			// Storing downloaded data for plotting
			final_results.emplace_back(map_data, "downloaded");

			// Performing mean return analysis
			auto mean_return_calculator = std::make_unique<historical_mean_return_calculator>();
			const financial_data_analyzer analyzer1(std::move(mean_return_calculator));
			double mean_return = analyzer1.analyze_data(stock_data);

			// Asserting positive mean return
			Assert::IsTrue(mean_return > 0.0, L"Expected positive return for the fetched stock data.");

			// Performing volatility analysis
			auto volatility_calculator = std::make_unique<historical_volatility_calculator>();
			const financial_data_analyzer analyzer2(std::move(volatility_calculator));
			double volatility = analyzer2.analyze_data(stock_data);

			// Asserting non-negative volatility
			Assert::IsTrue(volatility >= 0.0, L"Expected non-negative volatility for the fetched stock data.");

			// Setting up a random number generator for simulations
			std::unique_ptr<random_base> generator = std::make_unique<random_park_miller>(1);

			// Number of simulations to perform
			int number_simulations = 200;

			// Initializing the stock price simulator
			stock_price_simulator simulator(stock_data[0], mean_return, volatility, std::move(generator));

			// Calculating the time period for simulation
			double T = compute_expiry_time(stock_start_date, stock_end_date);
			// Setting the number of intervals for the simulation
			std::size_t intervals_count = 252;

			// Generating dates for each interval in the simulation
			std::vector<std::string> dates = generate_dates(stock_start_date, stock_end_date, intervals_count);

			// Running simulations and storing results
			for (int j = 0; j < number_simulations; j++)
			{
				std::vector<double> results_simulations = simulator.simulate_price_path(T, intervals_count);

				// Asserting matching sizes for dates and simulation results
				Assert::IsTrue(dates.size() == results_simulations.size());

				// Mapping dates to simulation results for plotting
				std::map<std::string, double> data_for_plotting;
				for (std::size_t i = 0; i < dates.size(); ++i)
				{
					data_for_plotting[dates[i]] = results_simulations[i];
				}
				final_results.emplace_back(data_for_plotting, "result_simulation" + std::to_string(j));
			}

			// Creating a script generator for plotting
			const std::unique_ptr<i_plot_script_generator> plot_script = std::make_unique<
				python_matplotlib_generator>();

			// Setting the file path for the generated plotting script
			const std::string file_path = "Plot_collected_data.py";

			// Generating the plot script with the collected data
			plot_script->generate(final_results, file_path, stock_ticker);

			// Checking if the script file exists and executing it
			if (std::filesystem::exists(file_path))
			{
				system("python Plot_collected_data.py ");
			}
			else
			{
				// Failing the test if the script file is not created
				Assert::Fail(L"The script file was not created.");
			}
		}
	};
}
