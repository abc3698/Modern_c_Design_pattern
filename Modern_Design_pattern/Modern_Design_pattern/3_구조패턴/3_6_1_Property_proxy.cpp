#include <iostream>
#include <string>

template<typename T>
struct Property
{
	T value;

	Property(){}

	Property(const T init_val)
	{
		*this = init_val;
	}

	// Get 작업
	operator T()
	{
		return value;
	}

	// Set 작업
	T operator =(T new_val)
	{
		return value = new_val;
	}

	// string을 출력하기 위해 구현
	friend std::ostream& operator<<(std::ostream& os, const Property& obj)
	{
		return os << obj.value;
	}
};

struct Person
{
	Property<std::string> name;
	Property<int> id;
};

int main()
{
	Person p;
	p.id = 10;
	p.name = "Joe";	
	
	std::cout << p.id << " " << p.name <<  std::endl;
}