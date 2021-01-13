#pragma once
#include <string>
#include "Person.h"

struct ChatRoom
{
	std::vector<Person*> people;

	void join(Person* p);
	void broadcast(const std::string& orgin, const std::string& msg);

	void message(const std::string& orgin, const std::string& who,
		const std::string& msg);
};