#pragma once

#include <string>
#include <string>
#include <vector>

// Compute the expiry time in years from the start date to the end date
double compute_expiry_time(const std::string& start_date, const std::string& end_date);

// Generate a vector of dates between the initial date and the final date with a given number of intervals
std::vector<std::string> generate_dates(const std::string& initial_date, const std::string& final_date,
                                        std::size_t intervals);
