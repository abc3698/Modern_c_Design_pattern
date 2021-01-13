#include <iostream>
#include <string>
#include <vector>
#include <sstream> 

enum class OutputFormat
{
	MARKDOWN,
	HTML
};

struct LIstStrategy
{
	virtual void start(std::ostringstream& oss) {};
	virtual void end(std::ostringstream& oss) {};
	virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
};

template <typename T>
class TextProcessor
{
private:
	std::ostringstream oss;
	T list_strategy;

public:
	void append_list(const std::vector<std::string> items)
	{
		list_strategy.start(oss);
		for (auto& item : items)
			list_strategy.add_list_item(oss, item);
		list_strategy.end(oss);
	}

	std::string str() const { return oss.str(); }

	void clear()
	{
		oss.str("");
		oss.clear();
	}	
};

struct HtmlLIstStrategy : LIstStrategy
{
	void start(std::ostringstream& oss) override
	{
		oss << "<ul>" << std::endl;
	}

	void end(std::ostringstream& oss) override
	{
		oss << "</ul>" << std::endl;
	}

	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << "<li>" << item << "</li>" << std::endl;
	}
};

struct MarkdownLIstStrategy : LIstStrategy
{
	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << " * " << item << std::endl;
	}
};

int main()
{
	TextProcessor<HtmlLIstStrategy> tp1;	
	tp1.append_list({ "foo", "bar", "baz" });
	std::cout << tp1.str() << std::endl;

	TextProcessor<MarkdownLIstStrategy> tp2;	
	tp2.append_list({ "foo", "bar", "baz" });
	std::cout << tp2.str() << std::endl;

	return 0;
}