#include "ChatRoom.h"

void ChatRoom::join(Person* p)
{
	std::string joinMsg = p->name + " joins the chat";
	broadcast("room", joinMsg);
	p->room = this;
	people.push_back(p);
}

void ChatRoom::broadcast(const std::string& orgin, const std::string& msg)
{
	for (auto p : people)
	{
		if (p->name != orgin)
			p->receive(orgin, msg);
	}
}

void ChatRoom::message(const std::string& orgin, const std::string& who,
	const std::string& msg)
{
	auto target = std::find_if(std::begin(people), std::end(people),
		[&](const Person* p) {return p->name == who;});

	if (target != std::end(people))
	{
		(*target)->receive(orgin, msg);
	}
}