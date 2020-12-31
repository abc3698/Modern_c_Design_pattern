#include <iostream>
#include "Person.h"
struct Person::PersonImple
{
	void greet(Person* p);
};

Person::Person() : impl(new PersonImple) {}
Person::~Person() { delete impl; }

void Person::greet()
{
	impl->greet(this);
}

void Person::PersonImple::greet(Person* p)
{
	std::cout << "Hello " << p->name << std::endl;
}