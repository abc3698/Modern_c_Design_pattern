#include <string>
#include <iostream>

struct Database
{
protected:
	Database() {}

public:
	static Database& get()
	{
		static std::shared_ptr<Database> db(new Database);	
		return *db;
	}

	Database(Database const&) = delete;
	Database(Database&&) = delete;
	Database& operator=(Database const&) = delete;
	Database& operator=(Database &&) = delete;
};

int main()
{
	Database& db = Database::get();
	std::cout << &db << std::endl;

	Database& db2 = Database::get();
	std::cout << &db2 << std::endl;
}