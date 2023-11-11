#include "pch.h"
#include "ConvergenceTable.h"

namespace stochastic_methods
{
	// Initializes the convergence table with an inner statistics handler to manage the collection of statistics.
	convergence_table::convergence_table(std::unique_ptr<statistics_handler> inner)
		: inner_(std::move(inner)), stop_point_(2), paths_done_(0) // Set initial stopping point and paths done.
	{
	}

	// Creates a clone of this convergence table, which is useful for copying the object polymorphically.
	std::unique_ptr<statistics_mc> convergence_table::clone() const
	{
		return std::make_unique<convergence_table>(*this); // Utilize the copy constructor for cloning.
	}

	// Copy constructor that ensures a deep copy of the convergence table including its inner statistics handler.
	convergence_table::convergence_table(const convergence_table& other)
		: results_so_far_(other.results_so_far_), stop_point_(other.stop_point_), paths_done_(other.paths_done_)
	{
		// Clone the inner statistics handler if it exists.
		if (other.inner_)
			this->inner_ = std::make_unique<statistics_handler>(*other.inner_);
	}

	// Takes a single result and adds it to the statistics handler, checking if the convergence point is reached.
	void convergence_table::dump_one_result(const double result)
	{
		inner_->dump_one_result(result); // Add the result to the inner statistics handler.
		++paths_done_; // Increment the number of paths processed.

		// If the number of paths processed reaches a stopping point, record the result.
		if (paths_done_ == stop_point_)
		{
			stop_point_ *= 2; // Increase the stopping point by a factor of two for logarithmic spacing.
			const std::vector<std::vector<double>> this_result = inner_->get_results_so_far();

			// Capture the intermediate results for convergence monitoring.
			for (const auto& value : this_result)
			{
				std::vector<double> temp_result;
				temp_result = value;
				temp_result.push_back(paths_done_); // Append the current number of paths processed to the result.
				results_so_far_.push_back(temp_result); // Add the intermediate results to the overall results.
			}
		}
	}

	// Retrieves the collection of results gathered so far, including any new results since the last stopping point.
	std::vector<std::vector<double>> convergence_table::get_results_so_far() const
	{
		std::vector<std::vector<double>> tmp = results_so_far_; // Start with the current stored results.

		// If the paths done is not at the next stopping point, fetch the latest results.
		if (paths_done_ * 2 != stop_point_)
		{
			const std::vector<std::vector<double>> this_result = inner_->get_results_so_far();

			// Add the latest results to the temporary collection.
			for (const auto& result : this_result)
			{
				std::vector<double> temp_result = result;
				temp_result.push_back(paths_done_); // Append the current number of paths processed to the result.
				tmp.push_back(temp_result); // Add the new results to the temporary collection.
			}
		}

		return tmp; // Return the full set of results, both intermediate and latest.
	}
}
