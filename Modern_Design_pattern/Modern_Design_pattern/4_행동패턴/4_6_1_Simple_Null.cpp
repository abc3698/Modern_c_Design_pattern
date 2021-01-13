#include <iostream>
#include <string>

struct Logger
{
	virtual ~Logger() = default;
	virtual void info(const std::string& s) = 0;
	virtual void warn(const std::string& s) = 0;
};

struct BankAccount
{
	std::shared_ptr<Logger> log;
	std::string name;
	int balance = 0;

	BankAccount(const std::shared_ptr<Logger> &log, const std::string &name, int balance)
		: log{ log }, name{ name }, balance{ balance }{}

	void deposit(int amount)
	{
		balance += amount;
		log->info
		(
			"Deposited $" + std::to_string(amount) + " to " + name + ", balance is now $" + std::to_string(balance)
		);
	}
};

struct ConsoleLogger : Logger
{
	void info(const std::string& s)
	{
		std::cout << "INFO " << s << std::endl;
	}

	void warn(const std::string& s)
	{
		std::cout << "WARNING " << s << std::endl;
	}
};

struct NullLogger : Logger
{
	void info(const std::string& s)
	{
		
	}

	void warn(const std::string& s)
	{
		
	}
};

int main()
{	
	BankAccount ba{ std::make_shared<NullLogger>(), "John", 100 };
	ba.deposit(100);
}