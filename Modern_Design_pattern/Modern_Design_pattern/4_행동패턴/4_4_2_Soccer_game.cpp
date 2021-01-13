#include <iostream>
#include <string>
#include <boost/signals2.hpp>

struct EventData
{
	virtual ~EventData() = default;
	virtual void print() const = 0;
};

struct PlayerScoredData : EventData
{
	std::string player_name;
	int goals_scored_so_far;

	PlayerScoredData(const std::string player_name,	const int goals_scored_so_far)
		: player_name{ player_name }, goals_scored_so_far{ goals_scored_so_far }{}

	void print() const override
	{
		std::cout << player_name << " has scored! (their " 
			<< goals_scored_so_far << " goal)" << std::endl;
	}
};

struct Game
{
	boost::signals2::signal<void(EventData*)> events;
};

struct Player
{
	std::string name;
	int goals_scored = 0;
	Game& game;

	Player(const std::string name, Game& game) 
		: name{ name }, game{ game }{}

	void score()
	{
		++goals_scored;
		PlayerScoredData pd{ name, goals_scored };
		game.events(&pd);
	}
};

struct Coach
{
	Game& game;
	explicit Coach(Game& game) : game{ game } 
	{
		game.events.connect
		(
			[](EventData* e)
			{
				PlayerScoredData* pd = dynamic_cast<PlayerScoredData*>(e);
				if (pd)
				{
					if(pd->goals_scored_so_far < 3)
						std::cout << "Coach says : well done, " << pd->player_name << std::endl;
					else
						std::cout << "Coach says : Hat-trick!!!, " << pd->player_name << std::endl;
				}
			}
		);
	}
};

int main()
{
	Game game;
	Player player1{ "Son", game };
	Player player2{ "Kane", game };

	Coach coach{ game };

	player1.score();
	player1.score();
	player1.score();

	player2.score();

	return 0;
}