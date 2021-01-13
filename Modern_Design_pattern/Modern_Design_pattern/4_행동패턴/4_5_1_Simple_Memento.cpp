#include <iostream>
#include <string>

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

public:
	explicit BankAccount(const int balance)
		: balance{ balance } {}

	Memento deposit(int amount)
	{
		balance += amount;
		return { balance };
	}

	void restore(const Memento& m)
	{
		balance = m.balance;
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& obj)
	{
		return os << "balance: " << obj.balance;
	}
};

int main()
{
	BankAccount ba{ 100 };
	auto m1 = ba.deposit(50);
	auto m2 = ba.deposit(25);
	std::cout << ba << std::endl;

	// undo
	ba.restore(m1);
	std::cout << ba << std::endl;

	// redo
	ba.restore(m2);
	std::cout << ba << std::endl;
}



