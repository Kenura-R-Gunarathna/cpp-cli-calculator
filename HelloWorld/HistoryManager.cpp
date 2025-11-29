#include "HistoryManager.h"
#include <iostream>

HistoryManager::HistoryManager(const std::string& databaseName) : dbName(databaseName), db(nullptr) {}

HistoryManager::~HistoryManager() {
	if (db) sqlite3_close(db);
}

void HistoryManager::init() {
	if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
		return;
	}
	const char* createTableSQL = 
		"CREATE TABLE IF NOT EXISTS history ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"expression TEXT, result REAL);";
	char* errMsg = nullptr;
	if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Error creating table: " << errMsg << "\n";
		sqlite3_free(errMsg);
	}
}

void HistoryManager::log(std::string expression, double result) {
	const char* sql = "INSERT INTO history (expression, result) VALUES (?, ?);";
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, expression.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_double(stmt, 2, result);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
}

void HistoryManager::showHistory() {
	const char* sql = "SELECT id, expression, result FROM history;";
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
		std::cout << "Calculation History:\n";
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			const unsigned char* expression = sqlite3_column_text(stmt, 1);
			double result = sqlite3_column_double(stmt, 2);
			std::cout << id << ": " << expression << " = " << result << "\n";
		}
		sqlite3_finalize(stmt);
	} else {
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << "\n";
	}
}