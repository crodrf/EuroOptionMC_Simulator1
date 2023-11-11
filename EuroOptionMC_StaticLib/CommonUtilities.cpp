#include "pch.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// Function to compute the time to expiry in years, given two date strings.
double compute_expiry_time(const std::string& start_date, const std::string& end_date)
{
	// Initialize struct to zero to hold the start and end dates.
	std::tm start = {};
	std::tm end = {};
	// Use string streams to parse the date strings.
	std::istringstream start_stream(start_date);
	std::istringstream end_stream(end_date);

	// Parse the start and end date strings into the tm structs.
	start_stream >> std::get_time(&start, "%Y-%m-%d");
	end_stream >> std::get_time(&end, "%Y-%m-%d");

	// Convert tm structs to time_t to get the epoch time.
	const std::time_t start_time = std::mktime(&start);
	const std::time_t end_time = std::mktime(&end);

	// Calculate the difference in seconds between the two times.
	const double difference_in_seconds = std::difftime(end_time, start_time);

	// Define the number of seconds in an average year, accounting for leap years.
	constexpr double seconds_in_a_year = 365.25 * 24 * 60 * 60;

	// Return the difference in years by dividing by the number of seconds in a year.
	return difference_in_seconds / seconds_in_a_year;
}

// Function to generate a vector of date strings between two dates at specified intervals.
std::vector<std::string> generate_dates(const std::string& initial_date, const std::string& final_date,
                                        std::size_t intervals)
{
	// Initialize struct to zero to hold the initial and final dates.
	std::tm tm_initial = {};
	std::tm tm_final = {};
	// Use string streams to parse the date strings.
	std::stringstream ss_initial(initial_date);
	std::stringstream ss_final(final_date);

	// Parse the initial and final date strings into the tm structs.
	ss_initial >> std::get_time(&tm_initial, "%Y-%m-%d");
	ss_final >> std::get_time(&tm_final, "%Y-%m-%d");

	// Convert tm structs to time_point objects using the system clock.
	auto tp_initial = std::chrono::system_clock::from_time_t(mktime(&tm_initial));
	auto tp_final = std::chrono::system_clock::from_time_t(mktime(&tm_final));

	// Calculate the total duration between the initial and final dates.
	auto total_duration = tp_final - tp_initial;
	// Calculate the duration of each interval.
	auto interval_duration = total_duration / intervals;

	// Vector to store the generated date strings.
	std::vector<std::string> dates;
	// Reserve enough space for all dates to be generated.
	dates.reserve(intervals + 1);

	// Loop to generate date strings for each interval.
	for (std::size_t i = 0; i <= intervals; ++i)
	{
		// Convert the current time_point to time_t format.
		std::time_t tt = std::chrono::system_clock::to_time_t(tp_initial);
		// Initialize a tm struct to hold local time.
		tm local_tm = {};
		// Convert the time_t to a tm struct as local time.
		localtime_s(&local_tm, &tt);

		// Use a stringstream to format and store the date string.
		std::stringstream ss;
		ss << std::put_time(&local_tm, "%Y-%m-%d");
		// Add the formatted date string to the vector.
		dates.push_back(ss.str());

		// Increment the initial time_point by the interval duration to get the next date.
		tp_initial += interval_duration;
	}
	// Return the vector containing all the generated date strings.
	return dates;
}
