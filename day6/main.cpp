#include "fileinput.h"
#include "charmatrix.h"

enum Directions
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};
const char char_dirs[] = { '^', '>', 'v', '<' };
const char char_visited[] = { 'U', 'R', 'D', 'L' };
const char plus = '+';
const aoc::Vec2 vec_dirs[] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

aoc::CharMatrix wander(aoc::CharMatrix matrix, aoc::Vec2 position)
{
	int direction = UP;
	while (matrix.getCharAt(position + vec_dirs[direction]) != '\0')
	{
		if (matrix.getCharAt(position + vec_dirs[direction]) == '#')
		{
			direction++;
			if (direction > 3)
				direction = 0;
		}
		else
		{
			matrix.setCharAt(position, 'X');
			position = position + vec_dirs[direction];
			matrix.setCharAt(position, char_dirs[direction]);
		}
	}
	matrix.setCharAt(position, 'X');

	return matrix;
}

bool wanderInf(aoc::CharMatrix matrix, aoc::Vec2 position, aoc::Vec2 obstacle)
{
	matrix.setCharAt(obstacle, '#');
	int direction = UP;
	while (matrix.getCharAt(position + vec_dirs[direction]) != '\0')
	{
		if (matrix.getCharAt(position + vec_dirs[direction]) == '#')
		{
			direction++;
			if (direction > 3)
				direction = 0;
		}
		else
		{
			if (matrix.getCharAt(position) == char_visited[direction])
				return true; // This is an infinite loop!
			//if ()
			//if (matrix.getCharAt(position) == char_visited[(direction + 1) % 4])
				//matrix.setCharAt(position, plus);
			else
				matrix.setCharAt(position, char_visited[direction]);
			position = position + vec_dirs[direction];
			// matrix.setCharAt(position, char_dirs[direction]);
		}
	}
	return false;
}

int main()
{
	aoc::CharMatrix matrix(aoc::readWholeFile("actual.txt"));

	int direction = UP;
	aoc::Vec2 position(matrix.getCoordOf(char_dirs[direction]));

	aoc::CharMatrix result = wander(matrix, position);

	size_t total = 0;
	for (char c : result.data)
		if (c == 'X')
			total++;
	std::cout << "The total number of visited squares is: " << total << std::endl;

	// Part 2 ----------
	size_t obstacleTotal = 0;
	for (int i = 0; i < matrix.width; i++)
	{
		for (int j = 0; j < matrix.height; j++)
		{
			if (matrix.getCharAt(aoc::Vec2(i, j)) == '#')
				continue;
			if (wanderInf(matrix, position, aoc::Vec2(i, j)))
				obstacleTotal++;
			// std::cout << "trying: " << i << " " << j << std::endl;
		}
	}
	std::cout << "The total number of possible obstacles is: " << obstacleTotal << std::endl;

	return 0;
}