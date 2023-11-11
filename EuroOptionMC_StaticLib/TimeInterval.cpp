#include "pch.h"
#include "TimeInterval.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

double compute_expiry_time(const std::string& start_date, const std::string& end_date)
{
	std::tm start = {}; // Initialize tm struct to store the start date.
	std::tm end = {}; // Initialize tm struct to store the end date.
	std::istringstream start_stream(start_date); // Create a stream from the start date string.
	std::istringstream end_stream(end_date); // Create a stream from the end date string.

	start_stream >> std::get_time(&start, "%Y-%m-%d"); // Parse the start date string into the tm struct.
	end_stream >> std::get_time(&end, "%Y-%m-%d"); // Parse the end date string into the tm struct.

	// Convert tm struct for start date to time_t (seconds since the Unix epoch).
	const std::time_t start_time = std::mktime(&start);
	// Convert tm struct for end date to time_t (seconds since the Unix epoch).
	const std::time_t end_time = std::mktime(&end);

	// Calculate the difference in seconds between the end time and the start time.
	const double difference_in_seconds = std::difftime(end_time, start_time);

	// Define the number of seconds in a non-leap year.
	constexpr double seconds_in_a_year = 365.25 * 24 * 60 * 60;
	// Return the difference in years, which is the time to expiry in years.
	return difference_in_seconds / seconds_in_a_year;
}

std::vector<std::string> generate_dates(const std::string& initial_date, const std::string& final_date,
                                        std::size_t intervals)
{
	std::tm tm_initial = {}; // Initialize tm struct for the initial date.
	std::tm tm_final = {}; // Initialize tm struct for the final date.
	std::stringstream ss_initial(initial_date); // Create a stringstream from the initial date string.
	std::stringstream ss_final(final_date); // Create a stringstream from the final date string.

	ss_initial >> std::get_time(&tm_initial, "%Y-%m-%d"); // Parse the initial date string into the tm struct.
	ss_final >> std::get_time(&tm_final, "%Y-%m-%d"); // Parse the final date string into the tm struct.

	// Convert tm structs to time_point objects using the system clock.
	auto tp_initial = std::chrono::system_clock::from_time_t(mktime(&tm_initial));
	auto tp_final = std::chrono::system_clock::from_time_t(mktime(&tm_final));

	// Calculate the total duration between the initial and final dates.
	auto total_duration = tp_final - tp_initial;
	// Calculate the duration of each interval.
	auto interval_duration = total_duration / intervals;

	std::vector<std::string> dates; // Vector to hold all generated dates.
	dates.reserve(intervals + 1); // Reserve space in the vector for all dates to avoid reallocations.

	// Generate dates for each interval.
	for (std::size_t i = 0; i <= intervals; ++i)
	{
		// Convert the current time_point to time_t format.
		std::time_t tt = std::chrono::system_clock::to_time_t(tp_initial);
		tm local_tm = {}; // Create a tm struct to hold local time.
		localtime_s(&local_tm, &tt); // Convert time_t to tm as local time.

		// Create a stringstream to format the date as a string.
		std::stringstream ss;
		ss << std::put_time(&local_tm, "%Y-%m-%d"); // Format the date using the YYYY-MM-DD format.
		dates.push_back(ss.str()); // Add the formatted date to the vector.

		// Move to the next interval.
		tp_initial += interval_duration;
	}
	return dates; // Return the vector containing all generated dates.
}



