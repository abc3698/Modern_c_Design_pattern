#include <iostream>
#include <string>

class Game
{
public:
	explicit Game(int num_of_players) : num_of_players{ num_of_players } {}
	
	void run()
	{
		start();
		while (!have_winner())
			take_turn();
		std::cout << "Player " << get_winner() << " wins" << std::endl;
	}

protected:
	virtual void start() = 0;
	virtual bool have_winner() = 0;
	virtual void take_turn() = 0;
	virtual int get_winner() = 0;

	int cur_player{ 0 };
	int num_of_players;	
};

class Chess : public Game
{
private:
	int turns{ 0 };
	int max_turns{ 10 };

public:
	explicit Chess() : Game{ 2 } {}

protected:
	void start() override {};
	
	bool have_winner() override { return turns == max_turns; };
	
	void take_turn() override
	{
		std::cout << "Turn " << turns << " taken by player " << cur_player << std::endl;
		++turns;
		cur_player = (cur_player + 1) % num_of_players;
	}

	int get_winner() override { return cur_player; }
};

int main()
{
	Chess chess;
	chess.run();
}