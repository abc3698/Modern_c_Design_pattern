#include <boost/flyweight.hpp>
#include <iostream>

struct User
{
    boost::flyweight<std::string> first_name, last_name;

    User(const std::string& first_name, const std::string& last_name)
        : first_name(first_name), last_name(last_name) {}

	friend std::ostream& operator<<(std::ostream& os, const User& obj)
	{
		return os
			<< "first_name: " << obj.first_name <<
			" last_name: " << obj.last_name;
	}
};

int main()
{
	User john_doe{ "John", "Doe" };
	User chris_doe{ "Chris", "Doe" };

	std::cout << "John " << john_doe << std::endl;
	std::cout << "Chris " << chris_doe << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "john_doe first name address : " << &john_doe.first_name.get() << std::endl;
	std::cout << "chris_doe first name address : " << &chris_doe.first_name.get() << std::endl;
	std::cout << std::boolalpha
		<< (&john_doe.first_name.get() == &chris_doe.first_name.get()) << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "john_doe last name address : " << &john_doe.last_name.get() << std::endl;
	std::cout << "chris_doe last name address : " << &chris_doe.last_name.get() << std::endl;	
	std::cout << std::boolalpha
		<< (&john_doe.last_name.get() == &chris_doe.last_name.get()) << std::endl;

	return 0;
}