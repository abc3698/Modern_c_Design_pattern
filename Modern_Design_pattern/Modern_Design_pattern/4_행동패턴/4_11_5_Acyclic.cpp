#include <iostream>
#include <string>
#include <sstream> 

struct DoubleExpression;
struct AdditionExpression;

template<typename Visitable>
struct Visitor
{
	virtual void visit(Visitable& obj) = 0;
};

struct VisitorBase
{
	virtual ~VisitorBase() = default;
};

struct Expression
{
	virtual ~Expression() = default;

	virtual void accept(VisitorBase& obj)
	{
		using EV = Visitor<Expression>;

		if (auto ev = dynamic_cast<EV*>(&obj))
			ev->visit(*this);
	}
};

struct DoubleExpression : Expression
{
	double value;
	explicit DoubleExpression(const double value) : value{ value } {}

	virtual void accept(VisitorBase& obj)
	{
		using DEV = Visitor<DoubleExpression>;

		if (auto dev = dynamic_cast<DEV*>(&obj))
			dev->visit(*this);
	}
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
	
	virtual void accept(VisitorBase& obj)
	{
		using AEV = Visitor<AdditionExpression>;

		if (auto aev = dynamic_cast<AEV*>(&obj))
			aev->visit(*this);
	}
};

struct ExpressionPrinter : VisitorBase,
	Visitor<DoubleExpression>, Visitor<AdditionExpression>
{
	void visit(DoubleExpression& obj) override
	{
		oss << obj.value;
	}

	void visit(AdditionExpression& obj) override
	{
		oss << "(";
		obj.left->accept(*this);
		oss << "+";
		obj.right->accept(*this);
		oss << ")";
	}

	std::string str() const { return oss.str(); }
private:
	std::ostringstream oss;
};

int main()
{
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
	ep.visit(*e);	

	std::cout << ep.str() << std::endl;
}