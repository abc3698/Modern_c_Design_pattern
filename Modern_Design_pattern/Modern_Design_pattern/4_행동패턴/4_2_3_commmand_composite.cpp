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
	bool succeed;
	virtual void call() = 0;
	virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
	BankAccount& account;
	enum Action { deposit, withdraw } action;
	int amount;

	BankAccountCommand(BankAccount& account, const Action action, const int amount)
		: account{ account }, action{ action }, amount{ amount }
	{
		succeed = false;
	}

	void call() override
	{
		switch (action)
		{
		case BankAccountCommand::deposit:
			account.deposit(amount);
			succeed = true;
			break;
		case BankAccountCommand::withdraw:
			succeed = account.withdraw(amount);
			break;
		}
	}

	void undo() override
	{
		if (!succeed) return;
		std::cout << "Undo - ";

		switch (action)
		{
		case BankAccountCommand::deposit:			
			account.withdraw(amount);
			break;
		case BankAccountCommand::withdraw:
			account.deposit(amount);
			break;
		}
	}
};

struct CompositeBankAccountCommand : 
	std::vector<BankAccountCommand>, Command
{
	CompositeBankAccountCommand(const std::initializer_list<value_type>& item)
		: std::vector<BankAccountCommand>(item) {}

	void call() override
	{
		for (auto& cmd : *this)
			cmd.call();
	}

	void undo() override
	{
		for (auto it = rbegin(); it != rend(); ++it)
			it->undo();
	}
};

struct DependentCompositeCommand : CompositeBankAccountCommand
{
	explicit DependentCompositeCommand(const std::initializer_list<value_type>& item)
		: CompositeBankAccountCommand{ item } {}

	void call() override
	{
		bool ok = true;
		for (auto& cmd : *this)
		{
			if (ok)
			{
				cmd.call();
				ok = cmd.succeed;
			}
			else
			{
				cmd.succeed = false;
			}
		}
	}
};

struct MoneyTransferCommand : DependentCompositeCommand
{
	MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
		: DependentCompositeCommand
	{
		BankAccountCommand{from, BankAccountCommand::withdraw, amount},
		BankAccountCommand{to, BankAccountCommand::deposit, amount}
	} {}
};

int main()
{
	BankAccount from;
	BankAccount to;

	MoneyTransferCommand transfercmd{from, to, 700};	

	transfercmd.call();

	MoneyTransferCommand transfercmd2{ from, to, 100 };
	transfercmd2.call();
	transfercmd2.undo();
}