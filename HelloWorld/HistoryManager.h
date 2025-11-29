#pragma once
#include <string>
#include <sqlite3.h>

class HistoryManager {
private:
	sqlite3* db;
	std::string dbName;

public:
	HistoryManager(const std::string& databaseName);
	~HistoryManager();
	void init();
	void log(std::string expression, double result);
	void showHistory();
};
