#include "pch.h"
#include "UtilityFunctions.h"

#include <ctime> // Include for handling calendar time functions.
#include <iomanip> // Include for input/output stream manipulators.
#include <iostream>
#include <sstream>

namespace data
{
	// Constructs a URL for downloading historical financial data based on the provided ticker and date range.
	std::string construct_url(const std::string& ticker, const std::string& start_date, const std::string& end_date)
	{
		// Initialize time structures for the start and end dates.
		std::tm start_tm = {};
		std::tm end_tm = {};
		// Convert start and end date strings into time structures.
		std::istringstream start_stream(start_date);
		std::istringstream end_stream(end_date);
		// Parse the date strings according to the YYYY-MM-DD format.
		start_stream >> std::get_time(&start_tm, "%Y-%m-%d");
		end_stream >> std::get_time(&end_tm, "%Y-%m-%d");

		// Convert time structures to time_t (seconds since the Unix epoch).
		time_t start_timestamp = std::mktime(&start_tm);
		time_t end_timestamp = std::mktime(&end_tm);

		// Define the base URL for the financial data service.
		std::string base_url = "https://query1.finance.yahoo.com/v7/finance/download/";
		// Construct the full URL with the ticker, start and end timestamps, and query parameters.
		std::string full_url = base_url + ticker
			+ "?period1=" + std::to_string(start_timestamp)
			+ "&period2=" + std::to_string(end_timestamp)
			+ "&interval=1d&events=history&includeAdjustedClose=true";

		// Return the full URL string.
		return full_url;
	}
}
