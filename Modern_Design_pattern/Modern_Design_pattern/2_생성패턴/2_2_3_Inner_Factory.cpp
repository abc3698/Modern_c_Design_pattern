#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

struct Point
{
private:
	Point(const float x, const float y) : x{ x }, y{ y }{}

public:
	struct PointFactory
	{
	private:
		PointFactory() {}

	public:
		static Point NewCartesian(const float x, const float y)
		{
			return { x, y };
		}

		static Point NewPolar(const float r, const float theta)
		{
			return { r * cos(theta), r * sin(theta) };
		}
	};

public:
	float x, y;		
	typedef PointFactory Factory;
};

int main()
{	
	auto p1 = Point::Factory::NewCartesian(5, 5);

	std::cout << "Catersian : " << p1.x << " " << p1.y << std::endl;

	auto p2 = Point::Factory::NewPolar(5, M_PI_4);

	std::cout << "Polar : " << p2.x << " " << p2.y << std::endl;
}