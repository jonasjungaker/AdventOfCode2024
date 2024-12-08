#include "fileinput.h"
#include "charmatrix.h"
#include "stringhelper.h"

struct Antenna
{
	aoc::Vec2 position;
	char letter;

	Antenna(aoc::Vec2 pos, char c)
		: position(pos)
		, letter(c)
	{}
};

static std::vector<Antenna> getAntennas(const aoc::CharMatrix& map)
{
	std::vector<Antenna> antennas;
	for (int i = 0; i < map.width; i++)
	{
		for (int j = 0; j < map.height; j++)
		{
			char c = map.getCharAt(i, j);
			if (!aoc::isAlphanumeric(c))
				continue;
			antennas.emplace_back(aoc::Vec2(i, j), c);
		}
	}
	return antennas;
}

static void populateNodes(aoc::CharMatrix& map, const aoc::Vec2& pos1, const aoc::Vec2& pos2)
{
	aoc::Vec2 direction = pos1 - pos2;
	int i = 0;
	while (map.setCharAt(pos1 + (i * direction), '#'))
	{
		i++;
	}
	i = 0;
	while (map.setCharAt(pos2 - (i * direction), '#'))
	{
		i++;
	}
}

int main()
{
	std::string input = aoc::readWholeFile("test.txt");
	std::string actual = aoc::readWholeFile("actual.txt");

	{
		aoc::CharMatrix antennaMap(actual);
		std::vector<Antenna> antennas = getAntennas(antennaMap);

		// Here, we start adding nodes to the antennamap
		for (int i = 0; i < antennas.size(); i++)
		{
			for (int j = i + 1; j < antennas.size(); j++)
			{
				const Antenna& ant1 = antennas[i];
				const Antenna& ant2 = antennas[j];
				if (ant1.letter != ant2.letter)
					continue;
				antennaMap.setCharAt(ant1.position + (ant1.position - ant2.position), '#');
				antennaMap.setCharAt(ant2.position + (ant2.position - ant1.position), '#');
			}
		}
		std::cout << antennaMap.data << std::endl;
		std::cout << "The total number of antinodes is: " << std::count(antennaMap.data.begin(), antennaMap.data.end(), '#') << std::endl;
	}


	// Part 2 -----------
	aoc::CharMatrix antennaMap(actual);
	std::vector<Antenna> antennas = getAntennas(antennaMap);
	for (int i = 0; i < antennas.size(); i++)
	{
		for (int j = i + 1; j < antennas.size(); j++)
		{
			if (antennas[i].letter != antennas[j].letter)
				continue;
			populateNodes(antennaMap, antennas[i].position, antennas[j].position);
		}
	}
	std::cout << antennaMap.data << std::endl;
	std::cout << "The total number of antinodes is: " << std::count(antennaMap.data.begin(), antennaMap.data.end(), '#');

	return 0;
}