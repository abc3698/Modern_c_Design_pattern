#include <iostream>
#include <string>
#include <memory>
#include <vector>

enum class Color {Red, Green, Blue};
enum class Size { Small, Medium, Large };

struct Product
{
	std::string name;
	Color color;
	Size size;
};

//struct ProductFilter
//{
//	typedef std::std::vector<Product*> Items;
//
//	Items by_color(Items items, Color color)
//	{
//		Items result;
//		for (auto& i : items)
//		{
//			if (i->color == color)
//			{
//				result.push_back(i);
//			}
//		}
//		return result;
//	}
//
//	Items by_size(Items items, Size size)
//	{
//		Items result;
//		for (auto& i : items)
//		{
//			if (i->size >= size)
//			{
//				result.push_back(i);
//			}
//		}
//		return result;
//	}
//
//	Items by_color_and_size(Items items, Color color, Size size)
//	{
//		Items result;
//		for (auto& i : items)
//		{
//			if (i->color == color && i->size >= size)
//			{
//				result.push_back(i);
//			}
//		}
//		return result;
//	}
//};

template <typename T> struct AndSpecification;

template <typename T>
struct Specification
{
	virtual bool is_satisfied(T* item) = 0;

	AndSpecification<T> operator&&(Specification<T>&& other)
	{
		return AndSpecification<T>(*this, other);
	}
};

template <typename T>
struct Filter
{
	virtual std::vector<T*> filter(std::vector<T*> items, 
		Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
	std::vector<Product*> filter(std::vector<Product*> items, 
		Specification<Product>& spec) override
	{
		std::vector<Product*> result;
		for (auto& i : items)
		{
			if (spec.is_satisfied(i))
			{
				result.push_back(i);
			}
		}
		return result;
	}
};

struct ColorSpecification : public Specification<Product>
{
	Color color;

	explicit ColorSpecification(Color color) : color(color) {}

	bool is_satisfied(Product* item) override
	{
		return item->color == color;
	}
};

struct SizeSpecification : public Specification<Product>
{
	Size size;

	explicit SizeSpecification(Size size) : size(size) {}

	bool is_satisfied(Product* item) override
	{
		return item->size >= size;
	}
};

template <typename T>
struct AndSpecification : public Specification<T>
{
	Specification<T>& first;
	Specification<T>& second;
	
	AndSpecification(Specification<T>& first, Specification<T>& second)
		: first(first), second(second) {}

	
	bool is_satisfied(T* item) override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

int main()
{
	Product apple{ "Apple", Color::Green, Size::Small };
	Product tree{ "Tree", Color::Green, Size::Large };
	Product house{ "House", Color::Blue, Size::Large };

	std::vector<Product*> all{ &apple, &tree, &house };

	
	ColorSpecification green(Color::Green);
	SizeSpecification large(Size::Large);
	//AndSpecification<Product> green_and_large(large, green);
	auto spec = ColorSpecification{ Color::Green } &&
		SizeSpecification{ Size::Large };
	
	BetterFilter bf;
	for (auto& x : bf.filter(all, spec))
		std::cout << x->name << " is green and large\n";

	/*auto large_thing = bf.filter(all, green_and_large);
	for (auto& g : large_thing)
		std::cout << g->name << " is Large and green" << std::endl;*/	

	/*auto green_thing = bf.filter(all, green);
	for (auto& g : green_thing)
		std::cout << g->name << " is green" << std::endl;

	std::cout <<  std::endl;

	auto large_thing = bf.filter(all, Large);
	for (auto& g : large_thing)
		std::cout << g->name << " is Large" << std::endl;*/
}
