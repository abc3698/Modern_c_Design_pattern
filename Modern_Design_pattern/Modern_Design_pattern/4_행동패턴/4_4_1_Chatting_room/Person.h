#pragma once
#include <string>
#include <vector>

struct ChatRoom;

struct Person
{
	std::string name;
	ChatRoom* room = nullptr;
	std::vector<std::string> chat_log;

	Person(const std::string& name);

	// Receive Message
	void receive(const std::string& orgin, const std::string& msg);
	// Public Message
	void say(const std::string& msg) const;
	// Private Message
	void pm(const std::string& who, const std::string& msg) const;
};
