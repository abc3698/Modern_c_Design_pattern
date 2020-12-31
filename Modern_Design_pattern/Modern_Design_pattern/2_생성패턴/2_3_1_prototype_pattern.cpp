#include <iostream>
#include <string>
#include <memory>
struct Address
{
	std::string street, city;
	int suite;

	Address(const std::string& street, const std::string& city, const int suite)
		: street{ street }, city{ city }, suite{ suite }{}
};

struct Contact
{
	std::string name;
	std::shared_ptr<Address> address;

	Contact(const std::string name, std::shared_ptr<Address> address) :
		name{ name }, address{ address }{}

	Contact(const Contact& other) : name(other.name), 
		address{ std::make_shared<Address>(*other.address) }
	{		
	}

	Contact& operator=(const Contact& other)
	{
		if (this == &other)
			return *this;
		name = other.name;
		address = other.address;
		return *this;
	}
};

int main()
{
	Contact worker{ "", std::make_shared<Address>("123 East Dr", "London", 0) };
	
	Contact john = worker;
	john.name = "John Doe";
	john.address->suite = 10;

	std::cout << "john.address->suite : " << john.address->suite << std::endl; // 10
	std::cout << "worker.address->suite : " << worker.address->suite << std::endl; // 10
}