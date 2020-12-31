#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <boost/functional/hash.hpp>

class CPaintDC
{
public:
	void setPixel(const int x, const int y, const int color)
	{
		std::cout << "{" << x << "," << y << "} ";
	}
};

struct Point
{
	int x, y;

	friend std::size_t hash_value(const Point& obj)
	{
		std::size_t seed = 0x725C686F;
		boost::hash_combine(seed, obj.x);
		boost::hash_combine(seed, obj.y);
		return seed;
	}
};

struct Line
{
	Point start, end;

	friend std::size_t hash_value(const Line& obj)
	{
		std::size_t seed = 0x719E6B16;
		boost::hash_combine(seed, obj.start);
		boost::hash_combine(seed, obj.end);
		return seed;
	}
};

struct VectorObject
{
	virtual std::vector<Line>::iterator begin() = 0;
	virtual std::vector<Line>::iterator end() = 0;
};

struct VectorRectangle : VectorObject
{
private:
	std::vector<Line> lines;

public:
	VectorRectangle(int x, int y, int width, int height)
	{
		lines.emplace_back(Line{ Point{x, y}, Point{x + width, y} });
		lines.emplace_back(Line{ Point{x + width, y}, Point{x + width, y + height} });
		lines.emplace_back(Line{ Point{x, y}, Point{x, y + height} });
		lines.emplace_back(Line{ Point{x, y + height}, Point{x + width, y + height} });
	}

	std::vector<Line>::iterator begin() override
	{
		return lines.begin();
	}

	std::vector<Line>::iterator end() override
	{
		return lines.end();
	}
};

void DrawPoints(CPaintDC& dc,
	std::vector<Point>::iterator start,
	std::vector<Point>::iterator end)
{
	for (auto i = start; i != end; ++i)
	{
		dc.setPixel(i->x, i->y, 0);
	}
}

struct LineToPointAdapter
{
	typedef std::vector<Point> Points;

	virtual Points::iterator begin() { return points.begin(); }
	virtual Points::iterator end() { return points.end(); }

	LineToPointAdapter(Line& line)
	{
		int left = std::min(line.start.x, line.end.x);
		int right = std::max(line.start.x, line.end.x);

		int top = std::min(line.start.y, line.end.y);
		int bottom = std::max(line.start.y, line.end.y);

		int dx = right - left;
		int dy = line.end.y - line.start.y;

		// 가로 또는 세로 선분들만
		if (dx == 0)
		{
			for (int y = top; y <= bottom; ++y)
			{
				points.emplace_back(Point{ left, y });
			}
		}
		else if (dy == 0)
		{
			for (int x = left; x <= right; ++x)
			{
				points.emplace_back(Point{ x, top });
			}
		}
	}

private:
	Points points;
};

struct LineToPointCachingAdapter
{
	typedef std::vector<Point> Points;

	virtual Points::iterator begin() { return cache[line_hash].begin(); }
	virtual Points::iterator end() { return cache[line_hash].end(); }

	LineToPointCachingAdapter(Line& line)
	{
		static boost::hash<Line> hash;
		line_hash = hash(line);

		if (cache.find(line_hash) != cache.end())
		{			
			std::cout << "cache hit" << std::endl;
			return;
		}

		int left = std::min(line.start.x, line.end.x);
		int right = std::max(line.start.x, line.end.x);

		int top = std::min(line.start.y, line.end.y);
		int bottom = std::max(line.start.y, line.end.y);

		int dx = right - left;
		int dy = line.end.y - line.start.y;

		// 가로 또는 세로 선분들만
		Points points;
		if (dx == 0)
		{
			for (int y = top; y <= bottom; ++y)
			{
				points.emplace_back(Point{ left, y });
			}
		}
		else if (dy == 0)
		{
			for (int x = left; x <= right; ++x)
			{
				points.emplace_back(Point{ x, top });
			}
		}

		cache[line_hash] = points;
	}

private:
	std::size_t line_hash;
	static std::map<std::size_t, Points> cache;
};

std::map<std::size_t, LineToPointCachingAdapter::Points> LineToPointCachingAdapter::cache;

int main()
{
	std::vector<std::shared_ptr<VectorObject>> vectorObjs
	{
		std::make_shared<VectorRectangle>(10, 10 ,100, 100),
		std::make_shared<VectorRectangle>(30, 30 ,60, 60)
	};

	CPaintDC dc;	
	for (auto& lines : vectorObjs)
	{
		for (auto& line : *lines)
		{
			LineToPointCachingAdapter lpo{ line };
			//DrawPoints(dc, lpo.begin(), lpo.end());			
		}
	}

	std::cout << std::endl;

	std::vector<std::shared_ptr<VectorObject>> vectorObjs2
	{
		std::make_shared<VectorRectangle>(10, 10 ,100, 100)		
	};
	
	auto lines = std::make_shared<VectorRectangle>(10, 10, 100, 100);	

	for (auto& line : *lines)
	{		
		LineToPointCachingAdapter lpo{ line };
	}	

	return 0;
}