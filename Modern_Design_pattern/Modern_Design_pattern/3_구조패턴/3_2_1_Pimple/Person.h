#pragma once
#include <string>

struct Person
{
	std::string name;
	void greet();

	Person();
	~Person();

	class PersonImple;
	PersonImple* impl;
};