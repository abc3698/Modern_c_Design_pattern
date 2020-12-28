#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>

class Journal
{
public:
	std::string title;
	std::vector<std::string> entries;

	explicit Journal(const std::string& title) : title(title) {};	

	void add(const std::string& entry)
	{
		static int count = 1;
		entries.push_back(std::to_string(count++) + ": " + entry);
	}	

	const std::vector<std::string> const getEntries()
	{
		return entries;
	}
};

class PersistenceManager
{
public:
	static void save(const Journal &j, const std::string &filename)
	{		
		std::ofstream ofs(filename);
		for (auto s : j.entries)
		{
			ofs << s << std::endl;
		}
		ofs.close();
	}
};