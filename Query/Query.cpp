/////////////////////////////////////////////////////////////////////
// Query.cpp -  Defines functions for the different query operations to be performed.//
// ver 1.0																			 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018						 //
///////////////////////////////////////////////////////////////////////////////////////



#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include <iostream>
#include <iomanip>
#include <functional>
#include "query.h"

//using namespace NoSqlDb;

//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
{
	Utilities::putline(n, out);
};

///////////////////////////////////////////////////////////////////////
// DbProvider class
// - provides mechanism to share a test database between test functions
//   without explicitly passing as a function argument.

class DbProvider
{
public:
	NoSqlDb::DbCore<std::string>& db() { return db_; }
private:
	static NoSqlDb::DbCore<std::string> db_;
};

NoSqlDb::DbCore<std::string> DbProvider::db_;

//----< Function creating Database >-------------------------------

void makeDb()
{
	NoSqlDb::DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;
	NoSqlDb::DbElement<std::string> demoElem;
	demoElem.name("Ketul");
	demoElem.descrip("Student of CS");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("Database Testing");
	db.addtoDb("Mehta", demoElem);
	demoElem.name("Komal");
	demoElem.descrip("Student of Chemistry");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("Test Database");
	db.addtoDb("Shah", demoElem);
	demoElem.name("Shrushti");
	demoElem.descrip("Student of Arts");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("Test2");
	db.addtoDb("Parekh", demoElem);
	demoElem.name("Arjav");
	demoElem.descrip("Commerce Student");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("TestforArjav");
	db.addtoDb("Maniyar", demoElem);
	demoElem.name("Kairav");
	demoElem.descrip("Callible");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("Test Case");
	db.addtoDb("Acharya", demoElem);
	db["Mehta"].children().push_back("Shah");
	dbp.db() = db;
}

//----< Requirement 6 - Suppporting Queries >-------------------------------

bool testR6()
{
	DbProvider dbp;
	NoSqlDb::DbCore<std::string> db = dbp.db();
	showDb(db);
	Utilities::title("\n  Demonstrating Requirement #6 - Supporting Queries\n");

	//Query demonstrating description that starts with letter 'C'.

	std::cout << "\n\n  Description starting with letter 'C'.\n ";
	NoSqlDb::query_condition qc;
	qc.descript("C(.*)");
	NoSqlDb::Query<std::string> q(db);
	NoSqlDb::Query<std::string> q1(db);
	q.select(qc).show();

	//Query demonstrating Name that starts with letter 'K' and description that starts with letter 'S'.

	std::cout << "\n\n  Name starting with letter 'K', Description with letter 'S'.\n\n ";
	NoSqlDb::query_condition qc1;
	qc1.name("(K)(.*)");
	NoSqlDb::Query<std::string> q2(db);
	q2.select(qc1).show();
	NoSqlDb::Query<std::string> q3(db);
	q3.from(q.keys());
	NoSqlDb::Query<std::string> q4(db);
	q4.from(q2.keys());

	//Query demonstrating operation on children

	std::cout << "\n\n  Query demonstrating CHILD operation.\n";
	q.child("Mehta").show();
	std::cout << "\n\n";

	return true;
}

//----< Requirement 7 - Suppporting AND/OR operation >-------------------------------

bool testR7()
{
	DbProvider dbp;
	NoSqlDb::DbCore<std::string> db = dbp.db();
	showDb(db);
	Utilities::title("\n  Demonstrating Requirement #7 - Supporting AND/OR Operations.\n");
	NoSqlDb::query_condition qc;
	NoSqlDb::Query<std::string> q(db);
	NoSqlDb::Query<std::string> q1(db);
	NoSqlDb::query_condition qc1;
	NoSqlDb::Query<std::string> q2(db);
	NoSqlDb::Query<std::string> q3(db);
	q3.from(q.keys());
	NoSqlDb::Query<std::string> q4(db);
	q4.from(q2.keys());

	//Query demonstrating OR operation

	std::cout << "\n\n  Query demonstrating OR operation.\n";
	q.operation_OR(q2).show();

	//Query demonstrating AND operation

	std::cout << "\n\n  Query demonstrating AND operation.\n";
	q3.operation_AND(q4).show();

	return true;
}

#ifdef TEST_QUERY

int main()
{
	makeDb();
	testR6();
	testR7();
    return 0;
}
#endif