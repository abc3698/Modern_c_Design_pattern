#include <iostream>
#include "Person.h"
#include "ChatRoom.h"

Person::Person(const std::string& name) :
	name{ name } {}

// Receive Message
void Person::receive(const std::string& orgin, const std::string& msg)
{
	std::string s{ orgin + ": \"" + msg + "\"" };
	std::cout << "[" << name << "'s chat session]" << s << std::endl << std::endl;
	chat_log.emplace_back(s);
}
// Public Message
void Person::say(const std::string& msg) const
{
	room->broadcast(name, msg);
}
// Private Message
void Person::pm(const std::string& who, const std::string& msg) const
{
	room->message(name, who, msg);
}