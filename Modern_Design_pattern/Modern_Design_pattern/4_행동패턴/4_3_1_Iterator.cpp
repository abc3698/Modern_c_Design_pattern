#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::vector<std::string> names{ "John", "Jane", "Jill" ,"Jack" };
	
	// 1) iterator을 통한 접근
	std::vector<std::string>::iterator it = names.begin(); 
	// auto it = names.begin();
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;

	std::cout << std::endl;

	// 2) iterator 참조
	it = names.begin();
	it->append(" Cena");
	std::cout << *it << std::endl;
	std::cout << std::endl;

	// 3) 반복문
	it = names.begin();
	while (it != names.end())
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << std::endl;

	// 4) 역순회
	for (auto ri = std::rbegin(names); ri != std::rend(names); ++ri)
	{
		std::cout << *ri << std::endl;
	}
	std::cout << std::endl;

	// 5) 범위 기반 for
	for (auto& name : names)
	{
		std::cout << name << std::endl;
	}
}