#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>

struct Shape
{
	virtual std::string str() const = 0;
};

struct Circle : Shape
{
	float radius;

	Circle() {}

	explicit Circle(const float radius) : radius{ radius } {}

	void resize(float factor) { radius *= factor; }

	std::string str() const override
	{
		std::ostringstream oss;
		oss << "A Circle of Radius " << radius;
		return oss.str();
	}
};

struct Square : Shape
{
	float side;

	Square() {}

	explicit Square(const float side)
		: side{ side } {}

	void resize(float factor) { side *= factor; }

	std::string str() const override
	{
		std::ostringstream oss;
		oss << "A square with side " << side;
		return oss.str();
	}
};

template<typename T>
struct ColoredShape : T
{
	static_assert(std::is_base_of<Shape, T>::value,
		"Template argumnet nust be a shape");

	std::string color;

	template <typename...Args>
	ColoredShape(const std::string& color, Args ...args)
		: T(std::forward<Args>(args)...), color{ color }		
	{
	}


	std::string str() const override
	{
		std::ostringstream oss;
		oss << T::str() << " has the color " << color;
		return oss.str();
	}
};

template<typename T>
struct TransparentShape : T
{
	static_assert(std::is_base_of<Shape, T>::value,
		"Template argumnet nust be a shape");

	uint8_t transparency;

	template<typename...Args>
	TransparentShape(const uint8_t transparency, Args ...args)
		: T(std::forward<Args>(args)...), transparency{ transparency }
	{
	}

	std::string str() const override
	{
		std::ostringstream oss;
		oss << T::str() << " has " << static_cast<float>(transparency) / 255.f * 100.f \
			<< "% transparency";
		return oss.str();
	}
};

int main()
{
	TransparentShape<ColoredShape<Square>> red_transparent_square{128, "Red", 5};	
	std::cout << red_transparent_square.str();	
}