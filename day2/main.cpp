#include "fileinput.h"
#include "stringhelper.h"

enum Mode
{
	MODE_INCREASING,
	MODE_DECREASING,
	MODE_NONE
};

struct Sequence
{
	std::vector<int> levels;
	int index;
	Mode mode;

	Sequence(std::vector<int> levels)
		: levels(levels)
		, index(0)
		, mode(MODE_NONE)
	{

	}

	bool check()
	{
		for (int i = 0; i < levels.size() - 1; i++)
		{
			int diff = levels.at(i) - levels.at(i + 1);

			if (abs(diff) > 3 || abs(diff) < 1)
				return false;

			if (mode == MODE_NONE)
			{
				if (diff < 0)
					mode = MODE_DECREASING;
				if (diff > 0)
					mode = MODE_INCREASING;
			}
			if (diff < 0 && mode == MODE_INCREASING)
				return false;
			if (diff > 0 && mode == MODE_DECREASING)
				return false;
		}
		return true;
	}

	void remove(int index)
	{
		levels.erase(levels.begin() + index, levels.begin() + index + 1);
		mode = MODE_NONE;
	}
};

int main(int argc, char* argv[])
{
	std::vector<std::string> fileContents = aoc::readFile("actual.txt");

	int safenum = 0;
	for (const auto& line : fileContents)
	{
		std::vector<std::string> strings = aoc::splitstring(line, ' ');

		std::vector<int> levels;
		//std::cout << "A sequence: " << std::endl;
		for (const auto& string : strings)
		{
			//std::cout << "\tA string: " << string << std::endl;
			levels.emplace_back(std::stoi(string));
		}

		Sequence s(levels);
		if (s.check())
		{
			safenum++;
			continue;
		}
		for (int a = 0; a < s.levels.size(); a++)
		{
			Sequence s2 = s;
			s2.remove(a);
			if (s2.check())
			{
				safenum++;
				break;
			}
		}
	}

	std::cout << "Amount of safe sequences: " << safenum << std::endl;

	return 0;
}
