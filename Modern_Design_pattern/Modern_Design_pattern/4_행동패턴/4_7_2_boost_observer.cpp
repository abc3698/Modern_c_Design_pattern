#include <iostream>
#include <string>
#include <boost/signals2.hpp>

template<typename T>
struct Observable
{
	boost::signals2::signal<void(T&, const std::string&)> property_changed;
};

struct Person : Observable<Person>
{
	Person(const int age) : age{ age } {}

	bool get_can_vote() { return age >= 16; }

	int get_age() { return age; }
	void set_age(const int age)
	{
		if (this->age == age) return;
		if (this->age > age) return;

		auto old_can_vote = get_can_vote();

		this->age = age;
		property_changed(*this, "age");
		
		if (old_can_vote != get_can_vote())
			property_changed(*this, "can_vote");			
	}

private:
	int age;
};

int main()
{
	Person p{ 10 };
	auto conn = p.property_changed.connect
	(
		[](Person& p, const std::string& prop_name)
		{
			std::cout << "Person's " << prop_name << " has changed to " <<
				p.get_age() << std::endl;
		}
	);

	p.set_age(16);

	conn.disconnect();

	p.set_age(17);
}