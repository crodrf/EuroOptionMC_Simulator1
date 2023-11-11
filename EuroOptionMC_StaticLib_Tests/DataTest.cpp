#include "pch.h"

#include "CommonUtilities.h"
#include "CppUnitTest.h"
#include "DataFilterInclude.h"
#include "TimeInterval.h"
#include "UtilityFunctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data;

namespace unit_test1
{
	// Test class for functions within the 'data' namespace.
	TEST_CLASS(DataNamespaceTests)
	{
	public:
		// Set up before running each test method.
		TEST_METHOD_INITIALIZE(Setup)
		{
			// Set stock information for testing.
			const std::string stock_start_date = "2020-01-01";
			const std::string stock_end_date = "2021-01-01";
			const std::string stock_ticker = "AAPL";

			// Construct the URL for fetching stock data.
			stock_url_ = construct_url(stock_ticker, stock_start_date, stock_end_date);
			// Initialize the data collector with the URL and ticker.
			stock_data_collector_ = std::make_unique<financial_data_collector>(stock_url_, stock_ticker);

			// Fetch stock data and assert that the fetch was successful.
			const bool fetch_data_success = stock_data_collector_->fetch_data();
			Assert::IsTrue(fetch_data_success, L"Failed to fetch stock data!");

			// Retrieve the fetched stock price data.
			stock_data_ = stock_data_collector_->get_price_data();
		}

		// Test for calculating the historical mean return.
		TEST_METHOD(TestHistoricalMeanReturnCalculator)
		{
			// Create a mean return calculator.
			auto mean_return_calculator = std::make_unique<historical_mean_return_calculator>();
			// Create an analyzer with the mean return calculator.
			const financial_data_analyzer analyzer(std::move(mean_return_calculator));
			// Analyze the fetched stock data to calculate mean return.
			const double mean_return = analyzer.analyze_data(stock_data_);

			// Assert that the mean return is positive.
			Assert::IsTrue(mean_return > 0.0, L"Expected positive return for the fetched stock data.");
		}

		// Test for calculating the historical volatility.
		TEST_METHOD(TestHistoricalVolatilityCalculator)
		{
			// Create a volatility calculator.
			auto volatility_calculator = std::make_unique<historical_volatility_calculator>();
			// Create an analyzer with the volatility calculator.
			const financial_data_analyzer analyzer(std::move(volatility_calculator));
			// Analyze the fetched stock data to calculate volatility.
			const double volatility = analyzer.analyze_data(stock_data_);

			// Assert that the volatility is non-negative.
			Assert::IsTrue(volatility >= 0.0, L"Expected non-negative volatility for the fetched stock data.");
		}

		// Test for calculating the risk-free rate.
		TEST_METHOD(TestRiskFreeRateCalculator)
		{
			// Create a risk-free rate calculator.
			auto risk_free_calculator = std::make_unique<risk_free_rate_calculator>();
			// Create an analyzer with the risk-free rate calculator.
			const financial_data_analyzer analyzer(std::move(risk_free_calculator));
			// Analyze the fetched data to calculate the risk-free rate.
			const double risk_free_rate = analyzer.analyze_data(stock_data_);

			// Assert that the risk-free rate is positive.
			Assert::IsTrue(risk_free_rate > 0.0, L"Expected positive risk-free rate for the fetched data.");
		}

	private:
		// Member variables to hold the data collector, fetched data, and the stock URL.
		std::unique_ptr<financial_data_collector> stock_data_collector_;
		std::vector<double> stock_data_;
		std::string stock_url_;
	};
}
