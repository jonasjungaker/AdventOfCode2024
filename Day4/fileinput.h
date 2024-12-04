#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

namespace aoc
{
	std::string readWholeFile(const std::filesystem::path& filepath)
	{
		std::ifstream file;
		file.open(filepath);

		if (!file)
		{
			std::cout << "Could not open file: " << filepath << std::endl;
			return "";
		}

		std::string out;
		char buffer[1023 + 1]; // Make room for the '\0' character
		while (!file.eof())
		{
			// Read into the buffer from the file...
			file.read(buffer, 1023); // ... up to 1023 characters can be read into the buffer ...
			std::streamsize read = file.gcount(); // ... get how many character were actually read ...
			buffer[read] = '\0'; // ... and null terminate the buffer at the last read character.

			// Append the recently read characters to the output string
			out.append(buffer, 0, static_cast<uint64_t>(read));
		}

		return out;
	}

	struct InputFile
	{
		const std::string content;
		size_t cursor = 0;

		InputFile(std::filesystem::path path)
			: content(aoc::readWholeFile(path))
		{
		}

		InputFile(const InputFile& other) = default;
		InputFile(InputFile&& other) = default;
		InputFile& operator=(const InputFile& other) = default;
		InputFile& operator=(InputFile&& other) = default;
		~InputFile() = default;

		bool isAtEnd() const
		{
			return !(cursor < content.size());
		}

		char getNextChar()
		{
			return content.at(cursor++);
		}

		char peekNextChar()
		{
			return content.at(cursor);
		}
	};
}
