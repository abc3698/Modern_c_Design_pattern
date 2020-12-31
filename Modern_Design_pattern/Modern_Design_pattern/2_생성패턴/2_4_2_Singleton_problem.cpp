#include "pch.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>

class Database
{
public:
	virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public Database
{
private:
	SingletonDatabase() {/*DB에서 데이터 읽는 코드*/ }
	std::map<std::string, int> capitals;

public:
	SingletonDatabase(SingletonDatabase const&) = delete;
	void operator=(SingletonDatabase const&) = delete;

	static SingletonDatabase& get()
	{
		static SingletonDatabase db;
		return db;
	}

	int get_population(const std::string& name) override
	{
		return capitals[name];
	}
};

struct SingletonRecordFinder
{
	int total_population(std::vector<std::string>& names)
	{
		int result = 0;
		for (auto& name : names)
		{
			result += SingletonDatabase::get().get_population(name);
		}
		return result;
	}
};

struct ConfigurableRecordFinder
{
	Database& db;

	explicit ConfigurableRecordFinder(Database& db) : db(db) {}
	int total_population(std::vector<std::string>& names)
	{
		int result = 0;
		for (auto& name : names)
		{
			result += db.get_population(name);
		}
		return result;
	}
};

class DummyDatabase : public Database
{
	std::map<std::string, int> capitals;

public:
	DummyDatabase()
	{
		capitals["seoul"] = 100;
		capitals["Tokyo"] = 10;
		capitals["Beijing"] = 1;
	}

	int get_population(const std::string& name) override
	{
		return capitals[name];
	}
};


TEST(RecordFinderTests, DummyTotalPopulationTest)
{
	DummyDatabase db{};
	ConfigurableRecordFinder rf{ db };

	EXPECT_EQ(110, rf.total_population(std::vector<std::string>{"seoul", "Tokyo"}));
}
