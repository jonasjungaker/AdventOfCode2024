#include "fileinput.h"

struct vec2
{
	int64_t x = 0;
	int64_t y = 0;

	vec2(int64_t x, int64_t y)
		: x(x)
		, y(y)
	{}

	vec2 operator+(const vec2& other) const
	{
		return vec2(x + other.x, y + other.y);
	}

	vec2 operator-(const vec2& other) const
	{
		return vec2(x - other.x, y - other.y);
	}

	vec2 operator*(int64_t multiplier) const
	{
		return vec2(x * multiplier, y * multiplier);
	}

	bool operator==(const vec2& other) const
	{
		return (x == other.x && y == other.y);
	}

	int64_t getlen() const
	{
		return std::abs(x) + std::abs(y);
	}

	bool isOrthogonal(const vec2& other) const
	{
		// This is pretty hacky... doesn't truly mean orthogonalism
		int64_t a = x * y;
		int64_t b = other.x * other.y;
		return !(a + b);
	}
};

struct CharMatrix
{
	std::string data;
	size_t width = 0;
	size_t height = 0;

	CharMatrix(const std::string& s)
		: data(s)
	{
		width = data.find_first_of('\n');
		height = (data.size() / (width + 1)) + 1;
	}

	char getCharAt(int64_t x, int64_t y) const
	{
		if (x < 0 || y < 0)
			return '\0';
		if (static_cast<uint64_t>(x) >= width || static_cast<uint64_t>(y) >= height)
			return '\0'; // out of bounds character
		size_t index = (y * (width + 1)) + x;
		return data.at(index);
	}

	char getCharAt(vec2 pos) const
	{
		return getCharAt(pos.x, pos.y);
	}
};

namespace Directions
{
	vec2 none(0, 0);
	vec2 dirs[8] = {
		vec2(-1,  0),
		vec2(-1,  1),
		vec2( 0,  1),
		vec2( 1,  1),
		vec2( 1,  0),
		vec2( 1, -1),
		vec2( 0, -1),
		vec2(-1, -1)
	};
}

char g_matchword[] = "XMAS";
char g_matchword2[] = "MAS";

struct Word
{
	vec2 startingPos;
	vec2 direction;
	int64_t length = 0;

	Word(vec2 pos, vec2 dir, int64_t len)
		: startingPos(pos)
		, direction(dir)
		, length(len)
	{}
};

int main()
{
	std::string s = aoc::readWholeFile("test.txt");

	const CharMatrix matrix(s);
	std::vector<Word> words;
	for (size_t y = 0; y < matrix.height; y++)
	{
		for (size_t x = 0; x < matrix.width; x++)
		{
			if (matrix.getCharAt(static_cast<int64_t>(x), static_cast<int64_t>(y)) == g_matchword[0])
			{
				for (int i = 0; i < 8; i++)
					words.emplace_back(vec2(static_cast<int64_t>(x), static_cast<int64_t>(y)), Directions::dirs[i], 1);
			}
		}
	}

	uint64_t totalWords = 0;
	for (Word& word : words)
	{
		while (word.length < 4)
		{
			if (matrix.getCharAt(word.startingPos + (word.direction * word.length)) == g_matchword[word.length])
			{
				word.length++;
				if (word.length == 4)
					totalWords++;
			}
			else
			{
				break;
			}
		}
	}

	std::cout << "Total matched words " << g_matchword << " is: " << totalWords << std::endl;


	/// ------------------ PART 2 ------------------- ///
	std::vector<Word> words2;
	for (size_t y = 0; y < matrix.height; y++)
	{
		for (size_t x = 0; x < matrix.width; x++)
		{
			if (matrix.getCharAt(static_cast<int64_t>(x), static_cast<int64_t>(y)) == g_matchword2[0])
			{
				for (int i = 0; i < 8; i++)
					words2.emplace_back(vec2(static_cast<int64_t>(x), static_cast<int64_t>(y)), Directions::dirs[i], 1);
			}
		}
	}

	std::vector<Word> matched;
	for (Word& word : words2)
	{
		while (word.length < 3)
		{
			if (matrix.getCharAt(word.startingPos + (word.direction * word.length)) == g_matchword2[word.length])
			{
				word.length++;
				if (word.length == 3)
					matched.push_back(word);
			}
			else
			{
				break;
			}
		}
	}

	std::vector<vec2> crossPoints;
	for (size_t i = 0; i < matched.size(); i++)
	{
		const Word& word1 = matched.at(i);
		if (word1.direction.getlen() < 2)
			continue; // Skip
		for (size_t j = i + 1; j < matched.size(); j++)
		{
			const Word& word2 = matched.at(j);
			if (word2.direction.getlen() < 2)
				continue; // skip
			if (!(word1.direction.isOrthogonal(word2.direction)))
				continue; // skip

			vec2 imid = word1.startingPos + word1.direction;
			vec2 jmid = word2.startingPos + word2.direction;
			if (imid == jmid)
			{
				crossPoints.push_back(imid);
			}
		}
	}

	std::cout << "Total cross points: " << crossPoints.size() << std::endl;

	return 0;
}
