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

class TextProcessor
{
private:
	std::ostringstream oss;
	std::unique_ptr<LIstStrategy> list_strategy;

public:
	void append_list(const std::vector<std::string> items)
	{
		list_strategy->start(oss);
		for (auto& item : items)
			list_strategy->add_list_item(oss, item);
		list_strategy->end(oss);
	}

	std::string str() const { return oss.str(); }

	void clear()
	{
		oss.str("");
		oss.clear();
	}

	void set_output_format(const OutputFormat format);
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

void TextProcessor::set_output_format(const OutputFormat format)
{
	switch (format)
	{
	case OutputFormat::HTML:
		list_strategy = std::make_unique<HtmlLIstStrategy>();
		break;

	case OutputFormat::MARKDOWN:
		list_strategy = std::make_unique<MarkdownLIstStrategy>();
		break;
	}
}

int main()
{
	TextProcessor tp;
	tp.set_output_format(OutputFormat::HTML);
	tp.append_list({ "foo", "bar", "baz" });
	std::cout << tp.str() << std::endl;

	tp.clear();
	
	tp.set_output_format(OutputFormat::MARKDOWN);
	tp.append_list({ "foo", "bar", "baz" });
	std::cout << tp.str() << std::endl;

	return 0;
}