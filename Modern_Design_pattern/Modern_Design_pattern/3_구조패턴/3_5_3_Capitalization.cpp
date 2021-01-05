#include <iostream>
#include <string>
#include <vector>

class FormattedText
{
	std::string plainText;
	bool* caps;

public:
	explicit FormattedText(const std::string& plainText) :
		plainText(plainText) 
	{
		caps = new bool[plainText.length()];
		memset(caps, false, plainText.length());
	}

	~FormattedText()
	{
		delete[]caps;
	}

	void cpaitalize(int start, int end)
	{
		for (int i = start; i <= end; ++i)
		{
			caps[i] = true;
		}
	}

	friend std::ostream& operator <<(std::ostream& os, const FormattedText& obj)
	{
		std::string s;

		for (int i = 0; i < obj.plainText.length(); ++i)
		{
			char c = obj.plainText[i];
			s += (obj.caps[i] ? std::toupper(c) : c);
		}

		return os << s;
	}
};

class BetterFormattedText
{
public:
	struct TextRange
	{
		int start, end;
		bool capitalize;

		bool covers(int position) const
		{
			return position >= start && position <= end;
		}
	};

private:
	std::string plainText;
	std::vector<TextRange> formatting;

public:
	explicit BetterFormattedText(const std::string& plainText) :
		plainText(plainText){}

	TextRange& get_range(int start, int end)
	{
		formatting.emplace_back(TextRange{ start, end });
		return *formatting.rbegin();
	}

	friend std::ostream& operator <<(std::ostream& os, const BetterFormattedText& obj)
	{
		std::string s;

		for (int i = 0; i < obj.plainText.length(); ++i)
		{
			char c = obj.plainText[i];
			
			for (const auto& rng : obj.formatting)
			{
				if (rng.covers(i) && rng.capitalize)
					c = std::toupper(c);
				s += c;
			}
		}

		return os << s;
	}
};

int main()
{
	BetterFormattedText bft("This is a brave new world");
	bft.get_range(10, 15).capitalize = true;
	std::cout << bft << std::endl;
}

