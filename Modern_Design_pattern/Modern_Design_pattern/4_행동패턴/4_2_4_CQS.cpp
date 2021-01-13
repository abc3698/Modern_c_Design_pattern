#include <iostream>
#include <string>

struct CreatureCommand;
struct CreatureQuery;

enum class CreatureAbility { strength, agility };

class Creature
{
	int strength, agility;

public:
	Creature(const int strength, const int agility)
		: strength{ strength }, agility{ agility }{}

	void process_command(const CreatureCommand& cc);
	int process_query(const CreatureQuery& q) const;

	friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
	{
		return os
			<< "agility: " << obj.agility
			<< " strength: " << obj.strength;
	}

	void set_strength(int value);
	int get_strength();

	void set_agility(int value);
	int get_agility();
};

struct CreatureCommand
{
	enum Action {set, IncreaseBy, DecreaseBy} action;
	CreatureAbility ability;
	int amount;
};

struct CreatureQuery
{
	CreatureAbility ability;
};


void Creature::process_command(const CreatureCommand& cc)
{
	int* ability = nullptr;
	switch (cc.ability)
	{
	case CreatureAbility::strength:
		ability = &strength;
		break;

	case CreatureAbility::agility:
		ability = &agility;
		break;
	}

	switch (cc.action)
	{
	case CreatureCommand::set:
		*ability = cc.amount;
		break;

	case CreatureCommand::IncreaseBy:
		*ability += cc.amount;
		break;

	case CreatureCommand::DecreaseBy:
		*ability -= cc.amount;
		break;
	}
}

int Creature::process_query(const CreatureQuery& q) const
{
	switch (q.ability)
	{
	case CreatureAbility::agility: return agility;
	case CreatureAbility::strength: return strength;
	}

	return 0;
}

void Creature::set_strength(int value)
{
	process_command(
		CreatureCommand{ CreatureCommand::set, CreatureAbility::strength, value }
	);
}

void Creature::set_agility(int value)
{
	process_command(
		CreatureCommand{ CreatureCommand::set, CreatureAbility::agility, value }
	);
}

int Creature::get_strength()
{
	return process_query(
		CreatureQuery{ CreatureAbility::strength }
	);
}

int Creature::get_agility()
{
	return process_query(
		CreatureQuery{ CreatureAbility::agility }
	);
}

int main()
{
	Creature cc{10, 10};
	std::cout << cc << std::endl;

	cc.set_strength(999);
	std::cout << cc << std::endl;

	std::cout << "cc's agility is " << cc.get_agility() << std::endl;
	return 0;
}