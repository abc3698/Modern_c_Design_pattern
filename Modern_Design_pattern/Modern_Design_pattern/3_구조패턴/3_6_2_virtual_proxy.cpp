#include <iostream>
#include <string>

struct Image
{
	virtual void draw() = 0;
};

struct Bitmap : Image
{
	Bitmap(const std::string& filename)
	{
		std::cout << "Loading image from " << filename << std::endl;
	}

	void draw() override
	{
		std::cout << "Draw Image" << std::endl;
	}
};

struct LazyBitmap : Image
{
private:
	Bitmap* bmp{ nullptr };
	std::string filename;

public:
	LazyBitmap(const std::string& filename) : filename{filename}
	{}
	~LazyBitmap() { if (bmp) delete bmp; }

	void draw() override
	{
		if (!bmp)
			bmp = new Bitmap(filename);
		bmp->draw();
	}
};

int main()
{
	Bitmap bitmap{ "test.jpg" };
}