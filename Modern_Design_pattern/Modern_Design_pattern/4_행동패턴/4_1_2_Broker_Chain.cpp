#include <iostream>
#include <string>
#include <boost/signals2.hpp>

struct Query
{
	std::string creature_name;
	enum Argument {attack, defence} argument;
	int result;

	Query(const std::string& creature_name, const Argument argument, const int result)
		: creature_name(creature_name), argument(argument),	result(result)
	{}
};

// Mediator
struct Game
{
	boost::signals2::signal<void(Query&)> queries;
};

class Creature
{
	Game& game;
	int attack, defense;

public:
	std::string name;
	Creature(Game& game, const std::string& name, const int attack, const int defense)
		: game(game), attack(attack), defense(defense),	name(name)
	{}

	int getAttack() const 
	{		
		Query q{ name, Query::Argument::attack, attack };
		game.queries(q);				
		return q.result;
	}

	friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
	{
		return os
			<< "name: " << obj.name
			<< " attack: " << obj.getAttack() // note here
			<< " defense: " << obj.defense;
	}
};

class CreatureModifier
{
	Game& game;
	Creature& creature;

public:
	CreatureModifier(Game &game, Creature & creature) 
		: game{ game }, creature{ creature }{}
};

class DoubleAttackModifier : public CreatureModifier
{
	boost::signals2::connection conn;

public:
	DoubleAttackModifier(Game& game, Creature& creature)
		: CreatureModifier(game, creature)
	{
		conn = game.queries.connect([&](Query& q)
			{
				if (q.creature_name == creature.name &&
					q.argument == Query::Argument::attack)
					q.result *= 2;
			}
		);
	}

	~DoubleAttackModifier()
	{
		conn.disconnect();
	}
};

int main()
{
	Game game;
	Creature goblin{ game, "Goblin", 2, 2 };
	std::cout << goblin << std::endl;

	{
		DoubleAttackModifier dam{ game, goblin };
		std::cout << goblin << std::endl;		
	}

	std::cout << goblin << std::endl;
}