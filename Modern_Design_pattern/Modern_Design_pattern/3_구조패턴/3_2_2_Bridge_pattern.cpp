#include <iostream>
#include <memory>
struct Renderer
{
	virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRender : Renderer
{
	void render_circle(float x, float y, float radius) override
	{
		std::cout << "Drawing a vector circle of radius " << radius << std::endl;
	}
};

struct RasterRender : Renderer
{
	void render_circle(float x, float y, float radius) override
	{
		std::cout << "Rasterizing circle of radius " << radius << std::endl;
	}
};

struct Shape
{
protected:
	std::unique_ptr<Renderer> renderer;
	Shape(std::unique_ptr<Renderer> renderer) : renderer{ std::move(renderer) } {}

public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
	void setRenderer(std::unique_ptr<Renderer> renderer)
	{
		this->renderer = std::move(renderer);
	}
};

struct Circle : Shape
{
	Circle(std::unique_ptr<Renderer> renderer, float x, float y, float radius) :
		Shape{ std::move(renderer) }, x{ x }, y{ y }, radius{ radius }{}

	float x, y, radius;

	void draw() override
	{
		renderer->render_circle(x, y, radius);
	}

	void resize(float factor) override
	{
		radius *= factor;
	}
};

int main()
{	
	Circle circle{ std::make_unique<RasterRender>(), 5, 5, 5 };
	circle.draw();
	circle.resize(2);
	circle.draw();

	circle.setRenderer(std::make_unique<VectorRender>());
	circle.draw();
}