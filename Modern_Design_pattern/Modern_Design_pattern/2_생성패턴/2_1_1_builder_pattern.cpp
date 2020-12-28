#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <vector>

struct HtmlElement
{
	std::string name;
	std::string text;
	std::vector<HtmlElement> elements;
	const size_t indent_size = 2;	

	std::string str(int indent=0) const
	{
		std::ostringstream oss;		
		oss << "<" << name << ">" << std::endl;
		
		for (const auto& e : elements)
			oss << "\t<" << e.name << ">" << e.text << "</" << e.name << ">" << std::endl;			

		oss << "</" << name << ">" << std::endl;
		return oss.str();
	}
	
	struct HtmlBuilder
	{		
		HtmlElement* root = nullptr;

		HtmlBuilder(std::string root_name) {			
			root = new HtmlElement;
			root->name = root_name;
		}

		HtmlBuilder* add_child(const std::string& child_name, const std::string& child_text)
		{
			auto e = HtmlElement{ child_name, child_text };
			root->elements.push_back(e);
			return this;
		}

		std::string str() { return root->str(); }

		~HtmlBuilder()
		{
			if (root != nullptr)
				delete root;
		}
	};

	static std::unique_ptr<HtmlBuilder> build(std::string root_name)
	{
		return std::make_unique<HtmlBuilder>(root_name);
	}
	

protected:
	HtmlElement() {}
	HtmlElement(const std::string& name, const std::string& text)
		: name(name), text(text) {}
};

int main()
{
	auto builder = HtmlElement::build("ul");	
	builder->add_child("li", "hello")->add_child("li", "world");
	
	std::cout << builder->str() << std::endl;
}