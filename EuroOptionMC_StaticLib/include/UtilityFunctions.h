#pragma once
#include <string>

namespace data
{
	// Construct the URL for the Yahoo Finance API
	std::string construct_url(const std::string& ticker, const std::string& start_date, const std::string& end_date);
}