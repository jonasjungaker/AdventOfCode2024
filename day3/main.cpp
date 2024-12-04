#include <iostream>
#include <cctype>
#include "fileinput.h"

bool matchString(aoc::InputFile& file, const std::string& s)
{
	for (char c : s)
	{
		if (file.isAtEnd())
			return false;
		if (file.getNextChar() != c)
			return false;
	}
	return true;
}

bool getNumber(aoc::InputFile& file, int* i)
{
	*i = 0;

	size_t len = 0;
	size_t start = file.cursor;
	bool isnumber = false;
	while (std::isdigit(file.peekNextChar()))
	{
		if (file.isAtEnd())
			return false;
		//std::cout << file.peekNextChar() << std::endl;
		file.cursor++;
		isnumber = true;
		len++;
		if (len > 3)
		{
			return false;
		}
	}
	std::string sub = file.content.substr(start, len);
	if (isnumber)
		*i = std::stoi(sub);
	return isnumber;
}

int main(int argc, char* argv[])
{
	aoc::InputFile f("test.txt");
	uint64_t total = 0;
	int first = 0;
	int second = 0;
	bool enable = true;
	while (!f.isAtEnd())
	{
		if (!enable)
		{
			if (matchString(f, "do()"))
			{
				std::cout << "Enabled..." << std::endl;
				enable = true;
			}
			else
				continue;
		}
		if (f.peekNextChar() == 'd')
		{
			if (matchString(f, "don't()"))
			{
				std::cout << "Disabled..." << std::endl;
				enable = false;
				continue;
			}
		}
		if (!matchString(f, "mul("))
			continue;
		if (!getNumber(f, &first))
			continue;
		if (!(f.getNextChar() == ','))
			continue;
		if (!getNumber(f, &second))
			continue;
		if (!(f.getNextChar() == ')'))
			continue;
		total += first * second;
	}

	std::cout << "The total of multiplications is: " << total << std::endl;
	return 0;
}
