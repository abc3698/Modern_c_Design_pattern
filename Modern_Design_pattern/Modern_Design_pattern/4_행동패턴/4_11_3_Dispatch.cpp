#include <iostream>
#include <string>

struct Foo;
struct Bar;

void func(Foo* foo) {}
void func(Bar* bar) {}

struct Stuff 
{
	virtual void call() = 0;
};
struct Foo : Stuff 
{
	void call() override
	{
		func(this);
	}
};
struct Bar : Stuff 
{
	void call() override
	{
		func(this);
	}
};

int main()
{	
	Stuff* stuff = new Foo;
	stuff->call();
}