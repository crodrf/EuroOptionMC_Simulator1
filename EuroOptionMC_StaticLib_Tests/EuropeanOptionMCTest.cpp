#include "pch.h"

#include "CppUnitTest.h"
#include "DataFilterInclude.h"
#include "IncludePlot.h"
#include "IncludeStochasticMethods.h"
#include "TimeInterval.h"

#include <filesystem>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace stochastic_methods;
using namespace data;
using namespace plot;


namespace unit_test1
{
	TEST_CLASS(EuropeanOption)
	{
	public:
		// Test method for Monte Carlo simulation of European Options
		TEST_METHOD(MC)
		{
			// This vector will hold the final results of our simulations
			std::vector<std::pair<std::map<std::string, double>, std::string>> final_results;

			// Define the start and end dates for the stock data, as well as the ticker symbol
			const std::string stock_start_date = "2020-01-01";
			const std::string stock_end_date = "2021-01-01";
			const std::string stock_ticker = "AAPL";

			// Construct the URL to fetch stock data and create a data collector
			const auto stock_url = construct_url(stock_ticker, stock_start_date, stock_end_date);
			const auto data_collector = std::make_unique<financial_data_collector>(
				stock_url, stock_ticker);

			// Attempt to fetch the stock data and verify that it was successful
			const bool fetch_data_success = data_collector->fetch_data();
			Assert::IsTrue(fetch_data_success, L"Failed to fetch stock data!");

			// Retrieve the fetched stock price data
			const auto stock_data = data_collector->get_price_data();

			// Create a calculator for historical volatility and analyze the stock data
			auto volatility_calculator = std::make_unique<historical_volatility_calculator>();
			const financial_data_analyzer analyzer1(std::move(volatility_calculator));
			const double volatility = analyzer1.analyze_data(stock_data);

			// Encapsulate the volatility in a parameters object
			std::unique_ptr<parameter_inner> parameter_inner_sigma = std::make_unique<parameters_constant>(volatility);
			parameters sigma(std::move(parameter_inner_sigma));

			// Assert that the volatility is non-negative
			Assert::IsTrue(volatility >= 0.0, L"Expected non-negative volatility for the fetched stock data.");

			// Repeat the process for bond data to obtain the risk-free rate
			const std::string bond_ticker = "^TNX";
			const auto bond_url = construct_url(bond_ticker, stock_start_date, stock_end_date);
			const auto bond_data_collector = std::make_unique<financial_data_collector>(
				bond_url, bond_ticker);

			// Fetch the bond data
			const bool bond_fetch_data_success = bond_data_collector->fetch_data();
			Assert::IsTrue(fetch_data_success, L"Failed to fetch bond data!");

			// Retrieve the fetched bond data
			const auto bond_data = bond_data_collector->get_price_data();

			// Create a calculator for the risk-free rate and analyze the bond data
			auto risk_free_rate = std::make_unique<risk_free_rate_calculator>();
			const financial_data_analyzer analyzer2(std::move(risk_free_rate));
			const double rfr = analyzer2.analyze_data(bond_data);

			// Encapsulate the risk-free rate in a parameters object
			std::unique_ptr<parameter_inner> parameter_inner_r = std::make_unique<parameters_constant>(rfr);
			parameters r(std::move(parameter_inner_r));

			// Create a random number generator for the Monte Carlo simulation
			std::unique_ptr<random_base> generator = std::make_unique<random_park_miller>(1);

			// Compute the time to expiry for the option
			double expiry = compute_expiry_time(stock_start_date, stock_end_date);

			// Create a payoff object for a European call option
			std::unique_ptr<i_payoff> eu_call_option = std::make_unique<european_call_payoff>(120);

			// Create a vanilla option object with the call payoff and expiry
			auto call_option = std::make_unique<vanilla_option>(std::move(eu_call_option), expiry);

			// Set up the Monte Carlo simulation with the option, volatility, risk-free rate, and random number generator
			european_option_mc option_mc(std::move(call_option), sigma, r, std::move(generator));

			// Run the price simulation
			option_mc.price(stock_data[0], 1000000);

			// Retrieve and check the simulation results
			if (auto results = option_mc.get_results_so_far(); !results.empty() && results[0].size() >= 2)
			{
				// Get the index for the last set of results and retrieve the mean price
				int index = static_cast<int>(results.size()) - 1;
				double mean_price = results[index][0];

				// Verify the mean price falls within an expected range
			//	Assert::IsTrue(mean_price >  && mean_price < , L"Mean price out of expected range.");

				// Verify that the sample size matches expectations
				double sample_size = results[0][1];
				Assert::IsTrue(2 == sample_size, L"Sample size mismatch.");
			}
			else
			{
				// If no results are produced, or they don't meet our size criteria, fail the test
				Assert::Fail(L"Simulation did not produce expected results.");
			}
		}
	};
}
