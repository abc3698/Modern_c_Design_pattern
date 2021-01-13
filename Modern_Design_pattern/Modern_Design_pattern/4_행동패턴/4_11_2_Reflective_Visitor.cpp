#include <iostream>
#include <string>
#include <sstream> 

struct Expression
{
	virtual ~Expression() = default;
};

struct DoubleExpression : Expression
{
	double value;
	explicit DoubleExpression(const double value) : value{ value } {}
};

struct AdditionExpression : Expression
{
	Expression* left, * right;

	AdditionExpression(Expression* const left, Expression* const right)
		: left{ left }, right{ right } {}

	~AdditionExpression()
	{
		delete left;
		delete right;
	}
};

struct ExpressionPrinter
{
	std::ostringstream oss;

	void print(Expression* e) 
	{
		if (auto de = dynamic_cast<DoubleExpression*>(e))
		{
			oss << de->value;
		}
		else if (auto ad = dynamic_cast<AdditionExpression*>(e))
		{
			oss << "(";
			print(ad->left);
			oss << "+";
			print(ad->right);
			oss << ")";
		}
	}

	std::string str() const { return oss.str(); }
};

int main()
{
	// 1. + (2. + 3.)
	auto e = new AdditionExpression
	{
		new DoubleExpression{1},
		new AdditionExpression
		{
			new DoubleExpression{2},
			new DoubleExpression{3}
		}
	};

	ExpressionPrinter ep;
	ep.print(e);	
	std::cout << ep.str() << std::endl;
}