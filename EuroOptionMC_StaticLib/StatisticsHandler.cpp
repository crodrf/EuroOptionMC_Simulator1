#include "pch.h"
#include "StatisticsHandler.h"

namespace stochastic_methods
{
	// Copy constructor creates a deep copy of the other statistics_handler if it has an associated statistics object.
	statistics_handler::statistics_handler(const statistics_handler& other)
	{
		// Check if the other stats_object_ is not null and clone it.
		if (other.stats_object_)
		{
			stats_object_ = other.stats_object_->clone();
		}
	}

	// Copy assignment operator ensures deep copy with clone to prevent slicing.
	statistics_handler& statistics_handler::operator=(const statistics_handler& other)
	{
		// Protect against self-assignment.
		if (this != &other)
		{
			// Clone the stats_object_ if it is not null, otherwise set to nullptr.
			stats_object_ = (other.stats_object_) ? other.stats_object_->clone() : nullptr;
		}
		return *this; // Return a reference to the current object.
	}

	// Move constructor transfers ownership of the statistics object to the new handler.
	statistics_handler::statistics_handler(statistics_handler&& other) noexcept : stats_object_(
		std::move(other.stats_object_)) // Use std::move to transfer ownership.
	{
	}

	// Move assignment operator for transferring ownership of the statistics object.
	statistics_handler& statistics_handler::operator=(statistics_handler&& other) noexcept
	{
		// Protect against self-assignment.
		if (this != &other)
		{
			stats_object_ = std::move(other.stats_object_); // Use std::move to transfer ownership.
		}
		return *this; // Return a reference to the current object.
	}

	// Record a single result by passing it to the encapsulated statistics object.
	void statistics_handler::dump_one_result(const double result) const
	{
		// Ensure that the stats_object_ is not null before trying to dump the result.
		if (stats_object_)
		{
			stats_object_->dump_one_result(result);
		}
	}

	// Fetch the results collected so far by the encapsulated statistics object.
	std::vector<std::vector<double>> statistics_handler::get_results_so_far() const
	{
		// If stats_object_ is not null, retrieve results, otherwise return an empty vector.
		return stats_object_ ? stats_object_->get_results_so_far() : std::vector<std::vector<double>>{};
	}

	// Clone the statistics handler, which includes cloning the encapsulated statistics object.
	std::unique_ptr<statistics_mc> statistics_handler::clone() const
	{
		// Clone the stats_object_ if it is not null, otherwise return nullptr.
		return stats_object_ ? stats_object_->clone() : nullptr;
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
