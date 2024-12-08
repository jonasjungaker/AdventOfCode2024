#include "fileinput.h"
#include "stringhelper.h"

struct Expression
{
	uint64_t target = 0;
	std::vector<uint64_t> operands;
};

enum class Operator
{
	ADD,
	MULT,
	CONCAT
};

std::vector<Operator> g_Operators = { Operator::ADD, Operator::MULT };

Expression extractExpression(const std::string& line)
{
	Expression e;
	std::string targetstr = line.substr(0, line.find(':'));
	e.target = std::stoull(targetstr.c_str());

	auto strops = aoc::splitstring(line.substr(line.find(':') + 2), ' ');
	for (const auto& op : strops)
	{
		e.operands.push_back(std::stoi(op));
	}

	return e;
}

struct OperatorPermutations
{
	std::vector<Operator> ops;

	OperatorPermutations(size_t size)
	{
		ops.reserve(size - 1);
		for (int i = 0; i < size - 1; i++)
			ops.push_back(Operator::ADD);
	}

	uint64_t evaluate(const Expression& e) const
	{
		uint64_t total = e.operands[0];
		for (int i = 0; i < ops.size(); i++)
		{
			switch (ops[i])
			{
			case Operator::ADD:
				total += e.operands[i + 1];
				break;
			case Operator::MULT:
				total *= e.operands[i + 1];
				break;
			case Operator::CONCAT:
				total = std::stoull(aoc::numToString(total) + aoc::numToString(e.operands[i + 1]));
				break;
			}
		}
		return total;
	}

	bool advance(int i = 0)
	{
		if (i >= ops.size())
			return false;
		switch (ops[i])
		{
		case Operator::ADD:
			ops[i] = Operator::MULT;
			return true;
		case Operator::MULT:
			ops[i] = Operator::CONCAT;
			return true;
		case Operator::CONCAT:
			ops[i] = Operator::ADD;
			return advance(i + 1);
		}
	}
};

void printExpr(Expression& e, OperatorPermutations op)
{
	std::cout << "Expression: " << e.target << " = ";
	std::cout << e.operands[0];
	for (int i = 0; i < op.ops.size(); i++)
	{
		switch (op.ops[i])
		{
		case Operator::ADD:
			std::cout << " + ";
			break;
		case Operator::MULT:
			std::cout << " * ";
			break;
		case Operator::CONCAT:
			std::cout << " || ";
			break;
		}
		std::cout << e.operands[i + 1];
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<std::string> lines = aoc::splitstring(aoc::readWholeFile("actual.txt"), '\n');

	uint64_t possible = 0;
	for (const auto& line : lines)
	{
		Expression e = extractExpression(line);

		OperatorPermutations pp(e.operands.size());

		do 
		{
			if (pp.evaluate(e) == e.target)
			{
				printExpr(e, pp);
				possible += e.target;
				break;
			}
		} while (pp.advance());
	}

	std::cout << "Total of calibrations: " << possible << std::endl;

	return 0;
}
