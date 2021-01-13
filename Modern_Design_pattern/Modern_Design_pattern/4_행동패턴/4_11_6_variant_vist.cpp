#include <iostream>
#include <string>
#include <variant>
#include <type_traits>

struct AddressPrinter
{
	void operator()(const std::string& house_name) const
	{
		std::cout << "A House called " << house_name << std::endl;
	}

	void operator()(const int house_number) const
	{
		std::cout << "House Number " << house_number << std::endl;
	}
};

int main()
{
	std::variant<std::string, int> house;
	house = "강원대학교";

	std::visit
	(
		[](auto& arg)
		{
			using T = std::decay_t<decltype(arg)>;

			if constexpr (std::is_same_v<T, std::string>)
			{
				std::cout << "A House called " << arg.c_str() << std::endl;
			}
			else
			{
				std::cout << "House Number " << arg << std::endl;
			}
		}, house
	);
}
