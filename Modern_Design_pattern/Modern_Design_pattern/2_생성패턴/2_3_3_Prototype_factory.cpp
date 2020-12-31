#include <iostream>
#include <string>
#include <memory>
struct Address
{
	std::string street, city;
	int suite;	

	friend std::ostream& operator<<(std::ostream& os, const Address& obj)
	{
		return os
			<< "street: " << obj.street
			<< " city: " << obj.city
			<< " suite: " << obj.suite;
	}
	
private:
	Address(const std::string& street, const std::string& city, const int suite)
		: street{ street }, city{ city }, suite{ suite }{}

public:
	friend struct Contact;
	friend struct EmployFactory;
};

struct Contact
{
	std::string name;
	std::shared_ptr<Address> address;
	
	Contact& operator=(const Contact& other)
	{
		if (this == &other)
			return *this;
		name = other.name;
		address = other.address;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Contact& obj)
	{
		return os
			<< "street: " << obj.name
			<< " address: {" << *obj.address << "}";
	}
	
private:
	Contact(const std::string name, std::shared_ptr<Address> address) :
		name{ name }, address{ address }{}

	Contact(const Contact& other) : name(other.name),
		address{ std::make_shared<Address>(*other.address) }
	{
	}

public:
	friend struct EmployFactory;
};

struct EmployFactory
{
	static Contact main;
	static Contact aux;	

	static std::unique_ptr<Contact> NewMainOfficeEmployee(const std::string name, const int suit)
	{
		return NewEmployee(name, suit, main);
	}

	static std::unique_ptr<Contact> NewAuxOfficeEmployee(const std::string name, const int suit)
	{
		return NewEmployee(name, suit, aux);
	}

private:
	static std::unique_ptr<Contact> NewEmployee(
		const std::string name, int suit, Contact& proto)
	{
		//auto result = std::make_unique<Contact>(proto);
		auto result = std::unique_ptr<Contact>{ new Contact{proto} };
		result->name = name;
		result->address->suite = suit;
		return result;
	}	
};

Contact EmployFactory::main = Contact{ "", std::shared_ptr<Address>{ new Address{"123 East Dr", "London", 0} } };
Contact EmployFactory::aux = Contact{ "", std::shared_ptr<Address>{ new Address{"477 West AA", "London", 0} } };

int main()
{
	auto john = EmployFactory::NewMainOfficeEmployee("John Doe", 123);
	std::cout << *john << std::endl;

	auto jane = EmployFactory::NewAuxOfficeEmployee("Jane Kim", 125);
	std::cout << *jane << std::endl;
}