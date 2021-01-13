#include <iostream>
#include <string>
#include <vector>

class BankAccount;

class Memento
{
	int balance = 0;
public:
	Memento(const int balance) : balance{ balance } {}
	friend class BankAccount;
};


class BankAccount
{
	int balance = 0;
	std::vector<std::shared_ptr<Memento>> changes;
	int current;

public:
	explicit BankAccount(const int balance)
		: balance{ balance } 
	{
		changes.emplace_back(std::make_shared<Memento>(balance));
		current = 0;
	}

	std::shared_ptr<Memento> deposit(int amount)
	{
		balance += amount;
		auto m = std::make_shared<Memento>(balance);
		changes.emplace_back(m);
		++current;
		return m;
	}

	void restore(const std::shared_ptr<Memento>& m)
	{
		if (m)
		{
			balance = m->balance;
			changes.emplace_back(m);
			current = changes.size() - 1;
		}		
	}

	std::shared_ptr<Memento> undo()
	{
		if (current > 0)
		{
			--current;
			auto m = changes[current];
			balance = m->balance;
			return m;
		}
		
		return {};
	}

	std::shared_ptr<Memento> redo()
	{
		if (current + 1 < changes.size())
		{
			++current;
			auto m = changes[current];
			balance = m->balance;
			return m;
		}
		return {};
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& obj)
	{
		return os << "balance: " << obj.balance;
	}
};

int main()
{
	BankAccount ba{ 100 };
	ba.deposit(50);
	ba.deposit(25);
	std::cout << ba << std::endl;

	// undo
	ba.undo();
	std::cout << "undo 1 : " << ba << std::endl;
	ba.undo();
	std::cout << "undo 2 : " << ba << std::endl;

	// redo
	ba.redo();
	std::cout << "redo 1 : " << ba << std::endl;

	// undo	
	ba.undo();
	std::cout << "undo 3 : " << ba << std::endl;
	ba.undo(); // 더 이상 Undo가 불가능한 상황
	std::cout << "undo 4 : " << ba << std::endl;
}