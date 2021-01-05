
#include <iostream>
#include <memory>
#include <map>
__interface HotDrink
{
	virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
	void prepare(int volume) override
	{
		std::cout << "Take tea bag, boil water, pour " << volume \
			<< "ml, add some lemon" << std::endl;
	}
};

struct Coffe : HotDrink
{
	void prepare(int volume) override
	{
		std::cout << "Take Coffee powder, boil water, pour " << volume 	\
			<< "ml" << std::endl;
	}
};

//enum class TYPE
//{
//	TEA, COFFEE
//};
//
//std::unique_ptr<HotDrink> make_drink(TYPE type)
//{
//	std::unique_ptr<HotDrink> drink;
//
//	if (type == TYPE::TEA)
//	{
//		drink = std::make_unique<Tea>();
//		drink->prepare(200);
//	}
//	else
//	{
//		drink = std::make_unique<Coffe>();
//		drink->prepare(50);
//	}
//
//	return drink;
//}

struct HotDrinkFactory
{
	virtual std::unique_ptr<HotDrink> make() = 0;
};

struct TeaFactory : HotDrinkFactory
{
	std::unique_ptr<HotDrink> make()
	{
		return std::make_unique<Tea>();
	}
};

struct CoffeeFactory : HotDrinkFactory
{
	std::unique_ptr<HotDrink> make()
	{
		return std::make_unique<Coffe>();
	}
};


enum class TYPE
{
	TEA, COFFEE
};


class DrinkFactory
{
private:
	std::map<TYPE, std::unique_ptr<HotDrinkFactory>> drink_factory;

public:
	DrinkFactory()
	{
		drink_factory[TYPE::COFFEE] = std::make_unique<CoffeeFactory>();
		drink_factory[TYPE::TEA] = std::make_unique<TeaFactory>();
	}

	std::unique_ptr<HotDrink> make_drink(const TYPE& type, const int volume)
	{
		auto p = drink_factory[type]->make();
		p->prepare(volume);
		return p;
	}
};

int main()
{	
	auto factory = DrinkFactory();
	
	auto drink = factory.make_drink(TYPE::COFFEE, 50);
}

