#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

struct Address
{
	std::string street, city;
	int suite;

	Address() {}
	Address(const std::string& street, const std::string& city, const int suite)
		: street{ street }, city{ city }, suite{ suite }{}

private:
	friend class boost::serialization::access;
	template<class Ar>
	void serialize(Ar& ar, const unsigned int version)
	{
		ar& street;
		ar& city;
		ar& suite;
	}
};

struct Contact
{
	std::string name;
	std::shared_ptr<Address> address;

	Contact() {}
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

private:
	friend class boost::serialization::access;
	template<class Ar>
	void serialize(Ar& ar, const unsigned int version)
	{
		ar& name;
		ar& address;
	}
};

int main()
{
	Contact worker{ "", std::make_shared<Address>("123 East Dr", "London", 0) };

	Contact john = worker;
	john.name = "John Doe";
	john.address->suite = 10;

	std::cout << "john.name : " << john.name << std::endl;

	// 직렬화
	std::ofstream output("john.dat", std::ios::binary);
	boost::archive::text_oarchive oa(output);
	oa << john;
	output.close();

	//// 역직렬화
	Contact john2;

	std::cout << "Before Deserialize john.name : " << john2.name << std::endl;

	std::ifstream input("john.dat", std::ios::binary);
	boost::archive::text_iarchive ia(input); 
	ia >> john2;
	input.close();

	std::cout << "After Deserialize john.name : " << john2.name << std::endl;
}