#pragma once
#include <vector>
#include <string>

namespace aoc
{
	std::vector<std::string> splitstring(const std::string& s, char delimiter)
	{
		std::vector<std::string> result;
		size_t start = 0;
		for (size_t end = s.find(delimiter, 0);; start = end + 1, end = s.find(delimiter, end + 1))
		{
			std::string newstring = s.substr(start, end - start);
			result.emplace_back(newstring);
			if (end == std::string::npos)
				break;
		}

		return result;
	}
}
