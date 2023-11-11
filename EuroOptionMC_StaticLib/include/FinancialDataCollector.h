#pragma once
#include <map>
#include <string>
#include <vector>
#include <curl/curl.h>

namespace data
{
	// Class to fetch data from a given URL
	class financial_data_collector
	{
		std::string source_url_; // URL to fetch data from
		std::vector<double> price_data_; // Vector to store price data
		std::string raw_data_; // String to store raw data
		std::string ticker_; // Ticker symbol
		std::map<std::string, double> date_to_price_map_; // Map to store date to price mapping

		static size_t curl_write_callback(void* contents, size_t size, size_t nmemb, void* userp);
		// Callback function for curl
		void parse_csv_data(const std::string& csv_data); // Parse CSV data
		void map_csv_data(const std::string& csv_data); // Map CSV data
		void save_data_to_file(const std::string& header_data) const; // Save data to file

	public:
		explicit financial_data_collector(std::string url, std::string ticker = "ticker");
		bool fetch_data(); // Fetch data from URL and parse it
		std::vector<double> get_price_data() const; // Return price data
		const std::map<std::string, double>& get_date_to_price_map(); // Return date to price map
	};
}
