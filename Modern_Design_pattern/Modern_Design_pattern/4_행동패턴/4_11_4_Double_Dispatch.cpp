#include <iostream>
#include <string>
#include <sstream> 

struct DoubleExpression;
struct AdditionExpression;

struct ExpressionVisitor
{
	virtual void visit(DoubleExpression* de) = 0;
	virtual void visit(AdditionExpression* ae) = 0;
};

struct Expression
{
	virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct DoubleExpression : Expression
{
	double value;
	explicit DoubleExpression(const double value) : value{ value } {}

	void accept(ExpressionVisitor* visitor) override
	{
		visitor->visit(this);
	}
};

struct AdditionExpression : Expression
{
	Expression* left, * right;

	AdditionExpression(Expression* const left, Expression* const right)
		: left{ left }, right{ right } {}

	void accept(ExpressionVisitor* visitor) override
	{
		visitor->visit(this);
	}

	~AdditionExpression()
	{
		delete left;
		delete right;
	}
};

struct ExpressionPrinter : ExpressionVisitor
{
	std::ostringstream oss;
	std::string str() const { return oss.str(); }

	void visit(DoubleExpression* de) override
	{
		oss << de->value;
	}

	void visit(AdditionExpression* ae)
	{
		oss << "(";
		ae->left->accept(this);
		oss << "+";
		ae->right->accept(this);
		oss << ")";
	}
};

struct ExpressionEvaluator : ExpressionVisitor
{
	double result;
	
	void visit(DoubleExpression* de) override
	{
		result = de->value;
	}

	void visit(AdditionExpression* ae)
	{		
		ae->left->accept(this);
		double temp = result;
		ae->right->accept(this);
		result += temp;
	}
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
	ep.visit(e);
	
	ExpressionEvaluator ee;
	ee.visit(e);

	std::cout << ep.str() << " = " << ee.result << std::endl;
}