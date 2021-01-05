#include <iostream>
#include <string>
#include <boost/bimap.hpp>
// 2^64개의 서로 다른 이름은 존재하지 않을 것이다.
typedef uint32_t key;

struct User
{
public:
	key first_name, last_name;

protected:
	// #include <boost/bimap.hpp>
	static boost::bimap<key, std::string> names;
	static key seed;	

public:
	User(const std::string& first, const std::string& last)
		: first_name{ add(first) }, last_name{ add(last) }{}

	const std::string& get_first_name() const
	{
		return names.left.find(first_name)->second;
	}

	const std::string& get_last_name() const
	{
		return names.left.find(last_name)->second;
	}

	friend std::ostream& operator<<(std::ostream& os, const User& obj)
	{
		return os
			<< "first_name: " << obj.first_name << " " << obj.get_first_name()
			<< " last_name: " << obj.last_name << " " << obj.get_last_name();
	}

protected:
	static key add(const std::string& s)
	{
		auto it = names.right.find(s);
		if (it == names.right.end())
		{						
			names.insert({ ++seed, s });
			return seed;
		}
		return it->second;
	}
};

key User::seed = 0;
boost::bimap<key, std::string> User::names{};

int main()
{
	User john_doe{ "John", "Doe" };
	User chris_doe{ "Chris", "Doe" };

	std::cout << "John " << john_doe << std::endl;
	std::cout << "Chris " << chris_doe << std::endl;

	return 0;
}