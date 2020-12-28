#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

struct Point
{
	float x, y;	

	// Friend 클래스를 통해 Point 생성자 접근을 
	// 가능하도록 함
	friend class PointFactory;
private:
	Point(const float x, const float y) : x{ x }, y{ y }{}
};

struct PointFactory
{
	static Point NewCartesian(const float x, const float y)
	{
		return { x, y };
	}

	static Point NewPolar(const float r, const float theta)
	{
		return { r * cos(theta), r * sin(theta) };
	}
};

int main()
{
	auto p1 = PointFactory::NewCartesian(5, 5);

	std::cout << "Catersian : " << p1.x << " " << p1.y << std::endl;

	auto p2 = PointFactory::NewPolar(5, M_PI_4);

	std::cout << "Polar : " << p2.x << " " << p2.y << std::endl;
}