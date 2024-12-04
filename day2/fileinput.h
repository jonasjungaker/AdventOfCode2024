#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

namespace aoc
{
	template<size_t BufferSize = 100>
	std::vector<std::string> readFile(const std::filesystem::path& filepath)
	{
		std::ifstream file;
		file.open(filepath);
		std::vector<std::string> result;

		if (!file)
		{
			std::cout << "Could not open file" << std::endl;
			return result;
		}

		char buffer[BufferSize]{};
		
		while (!file.eof())
		{
			file.getline(buffer, BufferSize, '\n');
			result.emplace_back(buffer);
		}

		return result;
	}
}
