#include <iostream>
#include <string>
#include <vector>

struct Tag
{
	std::string name;
	std::string text;
	std::vector<Tag> children;
	std::vector<std::pair<std::string, std::string>> attributes;

	friend std::ostream& operator<<(std::ostream &os, const Tag &tag)
	{
		os << "<" << tag.name;

		for (const auto& att : tag.attributes)
			os << " " << att.first << "=\"" << att.second << "\"";

		if (tag.children.size() == 0 && tag.text.length() == 0)
		{
			os << "/>" << std::endl;
		}
		else
		{
			os << ">" << std::endl;

			if (tag.text.length())
				os << tag.text << std::endl;

			for (const auto& child : tag.children)
				os << child;

			os << "</" << tag.name << ">" << std::endl;
		}

		return os;
	}

protected:
	Tag(const std::string &name, const std::string &text) : name{ name }, text{ text }{}
	Tag(const std::string &name, const std::vector<Tag> &children) 
		: name{ name }, children{ children }{}
};

struct P : Tag
{
	explicit P(const std::string& text)
		: Tag{ "p", text } {}

	// std::initializer_list<Tag>을 통해 Tag 배열 처럼 초기화 할 수 있음
	P(std::initializer_list<Tag> children)
		: Tag{ "p", children } {}
};

struct IMG : Tag
{
	explicit IMG(const std::string& url)
		: Tag{ "img", text } 
	{
		// emplace_back은 push_back과 같이 vector의 요소 끝에 원소를 추가하는 함수로
		// emplace_back과 같은 생성 삽입 함수는 삽입할 객체의 생성자를 위한 인자들을 받아 
		// std::vector 내에서 직접 객체를 생성하여 삽입 하므로 임시 객체의 생성과 파괴,
		// 복사(혹은 move)를 하지 않아도 되어 성능상 더 유리함
		attributes.emplace_back(make_pair("src", url));		
	}
};

int main()
{	
	std::cout <<
		P{
		  IMG {"http://pokemon.com/pikachu.png"},
		  IMG {"http://pokemon.com/pikachu2.png"}
		}
	<< std::endl;
	
	
	return 0;
}