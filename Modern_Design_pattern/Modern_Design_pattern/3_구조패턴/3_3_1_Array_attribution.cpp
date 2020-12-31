#include <iostream>
#include <array>
#include <functional>
#include <numeric>
#include <algorithm>

class Creature
{
	enum Abilities { strength, agility, intelligence, count };
	std::array<int, count> abilities;

public:
	int get_strength() const { return abilities[strength]; }
	void set_strength(int value) { abilities[strength] = value; }

	int get_agility() const { return abilities[agility]; }
	void set_agility(int value) { abilities[agility] = value; }

	int get_intelligence() const { return abilities[intelligence]; }
	void set_intelligence(int value) { abilities[intelligence] = value; }

	int sum() const
	{
		return std::accumulate(abilities.begin(), abilities.end(), 0);
	}

	double average() const
	{
		return sum() / (double)count;
	}

	int max() const
	{
		return *std::max_element(abilities.begin(), abilities.end());
	}
};

int main()
{	
	Creature orc;
	orc.set_strength(16);
	orc.set_agility(11);
	orc.set_intelligence(9);

	std::cout << "The orc has an average stat of "
		<< orc.average()
		<< " and a maximum stat of "
		<< orc.max()
		<< std::endl;

	return 0;
}