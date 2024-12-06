#pragma once
#include <string>

namespace aoc
{
	struct Vec2
	{
		int64_t x = 0;
		int64_t y = 0;

		Vec2(int64_t x, int64_t y)
			: x(x)
			, y(y)
		{}

		Vec2 operator+(const Vec2& other) const
		{
			return Vec2(x + other.x, y + other.y);
		}

		Vec2 operator-(const Vec2& other) const
		{
			return Vec2(x - other.x, y - other.y);
		}

		Vec2 operator*(int64_t multiplier) const
		{
			return Vec2(x * multiplier, y * multiplier);
		}

		bool operator==(const Vec2& other) const
		{
			return (x == other.x && y == other.y);
		}

		int64_t getlen() const
		{
			return std::abs(x) + std::abs(y);
		}

		bool isOrthogonal(const Vec2& other) const
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

		char getCharAt(Vec2 pos) const
		{
			return getCharAt(pos.x, pos.y);
		}

		void setCharAt(Vec2 pos, char c)
		{
			size_t index = (pos.y * (width + 1)) + pos.x;
			data.at(index) = c;
		}

		Vec2 getCoordOf(char c) const
		{
			size_t index = data.find(c);
			if (index == std::string::npos)
			{
				return Vec2(-1, -1);
			}
			uint64_t y = index / (width + 1);
			uint64_t x = index - (y * (width + 1));
			return Vec2(x, y);
		}
	};
}