#include<iostream>

class Rectangle
{
protected:
	int width, height;

public:
	Rectangle(const int width, const int height) : width(width), height(height) {}

	int get_width() const { return width; }
	int get_height() const { return height; }

	virtual void set_width(const int width) { this->width = width; }
	virtual void set_height(const int height) { this->height = height; }

	int area() { return width * height; }
};

class Square : public Rectangle
{
public:
	Square(const int size) : Rectangle(size, size) {}
	
	void set_width(const int width) override
	{ 
		this->width = this->height = width;
	}

	void set_height(const int height) override
	{
		this->width = this->height = height;
	}
};

void process(Rectangle& r)
{
	int w = r.get_width();
	r.set_height(10);

	std::cout << r.area() << std::endl;
}

int main()
{
	Square s{ 5 };
	process(s);
}
