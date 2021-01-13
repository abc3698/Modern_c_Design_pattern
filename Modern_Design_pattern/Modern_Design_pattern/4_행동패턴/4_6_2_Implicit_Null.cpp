#include <iostream>
#include <string>

struct Logger
{
	virtual ~Logger() = default;
	virtual void info(const std::string& s) = 0;
	virtual void warn(const std::string& s) = 0;
};

struct OptionalLogger : Logger
{
	std::shared_ptr<Logger> impl;
	static std::shared_ptr<Logger> no_logging;

	OptionalLogger(const std::shared_ptr<Logger> logger) : impl{ logger } {}

	void info(const std::string& s) override
	{
		if (impl) impl->info(s);
	}

	void warn(const std::string& s) override
	{
		if (impl) impl->warn(s);
	}
};

std::shared_ptr<Logger> OptionalLogger::no_logging{};

struct BankAccount
{
	std::shared_ptr<OptionalLogger> log;
	std::string name;
	int balance = 0;

	BankAccount(const std::string& name, int balance, const std::shared_ptr<Logger>& log = OptionalLogger::no_logging)
		: log{ std::make_shared<OptionalLogger>(log) }, name{ name }, balance{ balance }{}

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

int main()
{
	BankAccount ba1{"John", 100 };
	ba1.deposit(100);

	BankAccount ba2{ "Cena", 100, nullptr };
	ba2.deposit(100);

	BankAccount ba3{ "Kim", 100, std::make_shared<ConsoleLogger>()};
	ba3.deposit(100);
}