#include <iostream>
#include <memory>

struct ILogger 
{ 
	virtual void Log(const std::string& s) = 0; 
};

struct ConsoleLogger : ILogger 
{ 
	void Log(const std::string& s) override
	{ 
		std::cout << "ConsoleLogger: " << s.c_str() << std::endl;
	} 
}; 

struct TextLogger : ILogger
{
	void Log(const std::string& s) override
	{
		std::cout << "TextLogger: " << s.c_str() << std::endl;
	}
};

struct Car
{ 
	std::shared_ptr<ILogger> logger;

	void setLogger(const std::shared_ptr<ILogger> logger)
	{
		this->logger = logger;
		
	}

	void sendLog()
	{
		logger->Log("making a car");
	}
}; 

int main() 
{ 
	auto car = std::make_shared<Car>();
	car->setLogger(std::make_shared<ConsoleLogger>());
	car->sendLog();

	car->setLogger(std::make_shared<TextLogger>());
	car->sendLog();	
}
