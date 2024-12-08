#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <array>

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

	std::string numToString(uint64_t num)
	{
		std::ostringstream os;
		os << num;
		return os.str();
	}

	inline bool isAlphanumeric(char c)
	{
		return std::isalnum(static_cast<unsigned char>(c));
	}

	const std::array<char, 16> g_AlphaNumbers = {
		'A', 'B', 'C', 
		'a', 'b', 'c',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};
}
