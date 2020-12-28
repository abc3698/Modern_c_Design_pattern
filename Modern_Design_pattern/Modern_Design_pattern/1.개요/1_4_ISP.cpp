#include<iostream>

struct IPrinter
{
	virtual void print() = 0;
};

struct IFax
{
	virtual void fax() = 0;
};

struct IScan
{
	virtual void scan() = 0;
};

struct GVPrinter : public IPrinter
{
	void print() override
	{
		/*기능 구현*/
	}	
};

struct SSPrinter : public IPrinter, IScan
{
	void print() override
	{
		/*기능 구현*/
	}	
	void scan() override
	{
		/*기능 구현*/
	}
};

struct IMachine : public IPrinter, IFax, IScan
{
};

struct Machine : public IMachine
{
	IPrinter& _printer;
	IFax& _fax;
	IScan& _scan;

	Machine(IPrinter& printer, IFax& fax, IScan& scan)
		: _printer(printer), _fax(fax), _scan(scan) {}

	void print() override
	{
		_printer.print();
	}

	void fax() override
	{
		_fax.fax();
	}

	void scan() override
	{
		_scan.scan();
	}
};

struct APrinter : public IPrinter
{
	void print() override
	{
		std::cout << "Apinter" << std::endl;
	}
};

struct AFax : public IFax
{
	void fax() override
	{
		std::cout << "AFax" << std::endl;
	}
};

struct AScan : public IScan
{
	void scan() override
	{
		std::cout << "AScan" << std::endl;
	}
};

int main()
{
	APrinter printer;
	AFax fax;
	AScan scan;

	Machine machine{ printer, fax, scan };

	machine.print();
	machine.scan();
}