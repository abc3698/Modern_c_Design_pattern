#include <iostream>
#include <string>
#include <vector>

struct BankAccount
{
	int balance = 0;
	int overdraft_limit = -500;

	void deposit(int amount)
	{
		balance += amount;
		std::cout << "deposited " << amount << ", balace is now " <<
			balance << std::endl;
	}

	bool withdraw(int amount)
	{
		if (balance - amount >= overdraft_limit)
		{
			balance -= amount;
			std::cout << "withdrew " << amount << ", balace is now " <<
				balance << std::endl;
			
			return true;
		}
		return false;
	}
};

struct Command
{
	// deleted const keyword for undo
	virtual void call() = 0;
	virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
	BankAccount& account;
	enum Action { deposit, withdraw } action;
	int amount;
	bool withdrawal_succeeded;

	BankAccountCommand(BankAccount& account, const Action action, const int amount)
		: account{ account }, action{ action }, amount{ amount }, withdrawal_succeeded{false}{}

	void call() override
	{
		switch (action)
		{
		case BankAccountCommand::deposit:
			account.deposit(amount);
			break;
		case BankAccountCommand::withdraw:
			withdrawal_succeeded = account.withdraw(amount);
			break;
		}
	}

	void undo() override
	{
		switch (action)
		{
		case BankAccountCommand::deposit:
			std::cout << "Undo - ";
			account.withdraw(amount);
			break;
		case BankAccountCommand::withdraw:
			if (withdrawal_succeeded)
			{
				std::cout << "Undo - ";
				account.deposit(amount);
			}				
			else
			{
				std::cout << "withdraw command was failed " << std::endl;
			}
			break;
		}
	}
};

int main()
{
	BankAccount ba;
	BankAccountCommand cmd{ ba, BankAccountCommand::deposit, 100 };
	cmd.call();
	cmd.undo();

	BankAccountCommand cmd2{ ba, BankAccountCommand::withdraw, 700 };
	cmd2.call();
	cmd2.undo();
}