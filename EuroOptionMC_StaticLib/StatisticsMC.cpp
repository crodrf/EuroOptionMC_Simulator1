#include "pch.h"
#include "StatisticsMean.h"
#include "StatisticsMC.h"

namespace stochastic_methods
{
	// Record a single result by updating the running sum and incrementing the count of paths done.
	void statistics_mean::dump_one_result(const double result)
	{
		paths_done_++; // Increment the count of paths simulated.
		running_sum_ += result; // Add the new result to the running sum of results.
	}

	// Retrieve the mean of all results recorded so far, as a vector of a single vector containing the mean and count.
	std::vector<std::vector<double>> statistics_mean::get_results_so_far() const
	{
		std::vector<std::vector<double>> results;
		// Calculate the mean of all paths if any results have been recorded, otherwise return 0.
		double mean = (paths_done_ > 0) ? running_sum_ / paths_done_ : 0.0;
		// Push back the mean and the number of paths simulated into the results vector.
		results.push_back({mean, static_cast<double>(paths_done_)});
		return results; // Return the vector containing the mean result.
	}

	// Create a clone of the statistics_mean object, used for copying the object polymorphically.
	std::unique_ptr<statistics_mc> statistics_mean::clone() const
	{
		return std::make_unique<statistics_mean>(*this); // Utilize the copy constructor for cloning.
	}
}


/*
 * This portion of code is adapted from Mark Joshi's work in "C++ Design Patterns and Derivatives Pricing".
 * Copyright (c) 2002 Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
 */
