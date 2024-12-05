#include "fileinput.h"
#include "stringhelper.h"

static bool checkRule(int a, int b, std::pair<int, int> rule)
{
	if (a == rule.second && b == rule.first)
		return false;
	return true;
}

static bool checkSequence(const std::vector<std::string>& sequence, const std::vector<std::pair<int, int>>& rules)
{
	std::vector<int> seq;
	for (const auto& s : sequence)
	{
		seq.push_back(std::stoi(s));
	}

	for (int i = 0; i < seq.size(); i++)
	{
		for (int j = i + 1; j < seq.size(); j++)
		{
			for (const auto& rule : rules)
			{
				if (!checkRule(seq[i], seq[j], rule))
					return false;
			}
		}
	}
	return true;
}

static void adjustSequence(std::vector<std::string>& sequence, const std::vector<std::pair<int, int>>& rules)
{
	for (int i = 0; i < sequence.size(); i++)
	{
		for (int j = i + 1; j < sequence.size(); j++)
		{
			for (const auto& rule : rules)
			{
				if (!checkRule(std::stoi(sequence[i]), std::stoi(sequence[j]), rule))
					std::swap(sequence[i], sequence[j]);
			}
		}
	}
}

int main()
{
	std::vector<std::string> lines = aoc::splitstring(aoc::readWholeFile("actual.txt"), '\n');
	std::vector<std::pair<int, int>> rules;
	bool readRules = true;
	std::vector<std::vector<std::string>> goodSequences;
	std::vector<std::vector<std::string>> badSequences;

	for (auto line : lines)
	{
		if (line == "")
		{
			readRules = false;
			continue;
		}
		if (readRules)
		{
			std::vector<std::string> rule = aoc::splitstring(line, '|');
			std::pair<int, int> newrule(std::stoi(rule[0]), std::stoi(rule[1]));
			rules.push_back(newrule);
		}
		else
		{
			std::vector<std::string> sequence = aoc::splitstring(line, ',');
			if (checkSequence(sequence, rules))
				goodSequences.push_back(sequence);
			else
			{
				badSequences.push_back(sequence);
			}
		}
	}

	std::cout << "Total number of sequences passed rules: " << goodSequences.size() << std::endl;

	int total = 0;
	for (const auto& seq : goodSequences)
	{
		total += std::stoi(seq[seq.size() / 2]);
	}

	std::cout << "The answer is: " << total << std::endl;

	int badTotal = 0;
	for (auto& seq : badSequences)
	{
		while (!checkSequence(seq, rules))
		{
			adjustSequence(seq, rules);
		}
		badTotal += std::stoi(seq[seq.size() / 2]);
	}

	std::cout << "For the bad sequences, the total is: " << badTotal << std::endl;

	return 0;
}