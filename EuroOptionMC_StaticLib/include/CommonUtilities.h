#pragma once

#include <string>
#include <string>
#include <vector>

// Function that computes the expiry time of an option
double compute_expiry_time(const std::string& start_date, const std::string& end_date);

// Function that generates dates between two dates
std::vector<std::string> generate_dates(const std::string& initial_date, const std::string& final_date,
                                        std::size_t intervals);
