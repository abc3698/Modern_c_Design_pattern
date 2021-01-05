#include <iostream>
#include <string>
#include <functional>
struct Logger
{
	std::function<void()> func;
	std::string name;

	Logger(const std::function<void()>& func, const std::string& name)
		: func(func), name(name) {}

	void operator()() const
	{
		std::cout << "Entering" << name << std::endl;
		func();
		std::cout << "Exiting" << name << std::endl;
	}
};

template<typename T>
struct Logger2
{
	T func;
	std::string name;	

	Logger2(const T& func, const std::string& name)
		: func{ func }, name{ name } {}

	void operator()() const
	{
		std::cout << "Entering" << name << std::endl;
		func();
		std::cout << "Exiting" << name << std::endl;
	}
};

template<typename T>
auto make_logger2(T func, const std::string& name)
{
	return Logger2<T>{func, name};
}

void HelloFunction()
{
	std::cout << "Hello" << std::endl;
}

double add(double a, double b)
{
	std::cout << a << "+" << b << "=" << (a + b) << std::endl;
	return a + b;
}

// 다음 코드가 제대로 동작하기 위해서는 부분적인 특수화가 필요
template <typename> 
struct Logger3;

template<typename T, typename... Args>
struct Logger3<T(Args...)>
{
	std::function<T(Args ...)> func;	
	std::string name;

	Logger3(std::function<T(Args...)> func, const std::string& name)
		: func{ func },	name{ name }{}

	T operator() (Args ...args)
	{
		std::cout << "Entering" << name << std::endl;
		T result = func(args...);
		std::cout << "Exiting" << name << std::endl;
		return result;
	}
};

template <typename T, typename... Args>
auto make_logger3(T(*func)(Args...), const std::string& name)
{
	return Logger3<T(Args...)>(
		std::function<T(Args...)>(func), name
		);
}

int main()
{
	auto logged_add = make_logger3(add, "Add");
	auto result = logged_add(2, 3);
}