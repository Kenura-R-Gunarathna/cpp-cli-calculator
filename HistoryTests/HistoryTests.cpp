#include "pch.h"
#include "CppUnitTest.h"
#include <cstdio>
#include <vector>
#include <sqlite3.h>
#include "../HelloWorld/Calculator.h"
#include "../HelloWorld/HistoryManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HistoryTests
{
	TEST_CLASS(HistoryTests) 
	{
	public:

		const std::string TEST_DB = "test_unit_calc.db"; // Test database file

		TEST_METHOD_INITIALIZE(Setup) {					// Ensure test DB is removed before each test
            std::remove(TEST_DB.c_str());
        }

		TEST_METHOD_CLEANUP(Teardown) {					// Clean up test DB after each test
            std::remove(TEST_DB.c_str());
        }

		TEST_METHOD(TestDatabaseInitialization)
		{
			HistoryManager hm(TEST_DB);
			hm.init();

			sqlite3* db;
			int rc = sqlite3_open(TEST_DB.c_str(), &db);
			Assert::AreEqual(SQLITE_OK, rc, L"Database file should be created successfully");
			sqlite3_close(db);
		}

		TEST_METHOD(TestLogAndRetrieveHistory)
		{
			HistoryManager history(TEST_DB);
			history.init();
			// Log some calculations
			history.log("2 + 2", 4.0);
			history.log("sin(30, deg)", 0.5);
			history.log("log(100)", 2.0);
			// Retrieve and verify history
			sqlite3* db;
			Assert::AreEqual(SQLITE_OK, sqlite3_open(TEST_DB.c_str(), &db));
			const char* sql = "SELECT expression, result FROM history ORDER BY id;";
			sqlite3_stmt* stmt;
			Assert::AreEqual(SQLITE_OK, sqlite3_prepare_v2(db, sql, -1, &stmt, 0));
			std::vector<std::pair<std::string, double>> expected = {
				{"2 + 2", 4.0},
				{"sin(30, deg)", 0.5},
				{"log(100)", 2.0}
			};
			size_t index = 0;
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				std::string expr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
				double result = sqlite3_column_double(stmt, 1);
				Assert::AreEqual(expected[index].first, expr);
				Assert::AreEqual(expected[index].second, result, 0.0001);
				index++;
			}
			Assert::AreEqual(expected.size(), index); // Ensure all entries were checked
			sqlite3_finalize(stmt);
			sqlite3_close(db);
		}

	};
}
