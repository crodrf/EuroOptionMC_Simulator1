#include "pch.h"
#include "FinancialDataCollector.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace data
{
	financial_data_collector::financial_data_collector(std::string url, std::string ticker)
		: source_url_(std::move(url)), ticker_(std::move(ticker))
	{
	}

	// Callback function for libcurl data writing.
	size_t financial_data_collector::curl_write_callback(void* contents, const size_t size, const size_t nmemb,
	                                                     void* userp)
	{
		// Append the received data to the user-provided string.
		static_cast<std::string*>(userp)->append(static_cast<char*>(contents), size * nmemb);
		// Return the number of bytes handled to libcurl.
		return size * nmemb;
	}

	// Parse CSV data string to extract closing prices.
	void financial_data_collector::parse_csv_data(const std::string& csv_data)
	{
		// Stream used to process each line of the CSV data.
		std::stringstream ss(csv_data);
		// Variables used to store lines and values from the CSV.
		std::string line, value;

		// Ignore the header line.
		std::getline(ss, line);

		// Process each line to extract closing prices.
		while (std::getline(ss, line))
		{
			// Index of the closing price in the CSV format.
			constexpr int closing_price_index = 4;
			// Stream used to process each value within the line.
			std::stringstream line_stream(line);
			// Loop through each comma-separated value.
			for (int i = 0; std::getline(line_stream, value, ',') && i <= closing_price_index; ++i)
			{
				// When the closing price index is reached, add it to the price data vector.
				if (i == closing_price_index)
				{
					// Ensure that the value is not "null".
					if (value != "null")
					{
						price_data_.push_back(std::stod(value));
					}
				}
			}
		}
	}

	// Maps the CSV data into a date-to-price map for easy access.
	void financial_data_collector::map_csv_data(const std::string& csv_data)
	{
		// Stream used to process each line of the CSV data.
		std::stringstream ss(csv_data);
		// Variables used to store lines and values from the CSV.
		std::string line, value;

		// Ignore the header line.
		std::getline(ss, line);

		// Process each line to extract date and closing price pairs.
		while (std::getline(ss, line))
		{
			// Stream used to process each value within the line.
			std::stringstream line_stream(line);
			// Variables used to store the current date and price.
			std::string current_date;
			double current_price;

			// Loop through each comma-separated value.
			for (int i = 0; std::getline(line_stream, value, ','); ++i)
			{
				// Indexes for date and closing price in the CSV format.
				constexpr int closing_price_index = 4;
				constexpr int date_index = 0;
				// Extract the date.
				if (i == date_index)
				{
					current_date = value;
				}
				// Extract and store the closing price.
				if (i == closing_price_index)
				{
					// Ensure that the value is not "null".
					if (value != "null")
					{
						current_price = std::stod(value);
						// Map the date to the corresponding price.
						date_to_price_map_[current_date] = current_price;
					}
				}
			}
		}
	}

	// Saves the header data and raw CSV data to files.
	void financial_data_collector::save_data_to_file(const std::string& header_data) const
	{
		// Save header data to a text file.
		std::ofstream header_file("server_response_headers_" + ticker_ + ".txt");
		if (header_file.is_open())
		{
			header_file << header_data;
			header_file.close();
		}
		else
		{
			// Output an error message if the file cannot be opened.
			std::cerr << "Failed to open header file for writing." << std::endl;
		}

		// Save raw CSV data to a file.
		std::ofstream raw_data_file("historical_data_" + ticker_ + ".csv");
		if (raw_data_file.is_open())
		{
			raw_data_file << raw_data_;
			raw_data_file.close();
		}
		else
		{
			// Output an error message if the file cannot be opened.
			std::cerr << "Failed to open raw data file for writing." << std::endl;
		}
	}

	// Fetches financial data using cURL, parses it, maps it, and saves it to a file.
	bool financial_data_collector::fetch_data()
	{
		// String to hold the header data.
		std::string header_data;
		// Clear any existing raw data.
		raw_data_.clear();

		// Initialize cURL session.
		CURL* curl = curl_easy_init();
		if (!curl)
		{
			std::cerr << "Error: CURL initialization failed." << std::endl;
			return false;
		}

		// Set cURL options for the data collection.
		curl_easy_setopt(curl, CURLOPT_URL, source_url_.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &raw_data_);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, curl_write_callback);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_data);

		// Perform the cURL request.
		const CURLcode res = curl_easy_perform(curl);
		// Clean up cURL session.
		curl_easy_cleanup(curl);

		// Check for errors in the cURL request.
		if (res != CURLE_OK)
		{
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			return false;
		}

		// Parse, map, and save the CSV data fetched.
		parse_csv_data(raw_data_);
		map_csv_data(raw_data_);
		save_data_to_file(header_data);
		return true;
	}

	// Returns the price data as a vector of doubles.
	std::vector<double> financial_data_collector::get_price_data() const
	{
		return price_data_;
	}

	// Returns the date-to-price map.
	const std::map<std::string, double>& financial_data_collector::get_date_to_price_map()
	{
		return date_to_price_map_;
	}
}
