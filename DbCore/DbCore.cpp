/////////////////////////////////////////////////////////////////////
// DbCore.cpp - Implements NoSql database prototype                //
// ver 1.0                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////

#include "DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include <iostream>
#include <iomanip>
#include <functional>

using namespace NoSqlDb;

//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n=1, std::ostream& out = std::cout)
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
  DbCore<std::string>& db() { return db_; }
private:
  static DbCore<std::string> db_;
};

DbCore<std::string> DbProvider::db_;

///////////////////////////////////////////////////////////////////////
// test functions

//----< demo requirement #1 >------------------------------------------

bool testR1()
{
  Utilities::title("Demonstrating Requirement #1");
  std::cout << "\n  " << typeid(std::function<bool()>).name()
    << ", declared in this function, "
    << "\n  is only valid for C++11 and later versions.";
  putLine();
  return true; // would not compile unless C++11
}

//----< demo requirement #2 >------------------------------------------

bool testR2()
{
  Utilities::title("Demonstrating Requirement #2");
  std::cout << "\n  A visual examination of all the submitted code "
    << "will show only\n  use of streams and operators new and delete.";
  putLine();
  return true;
}

//----< demo first part of requirement #3 >----------------------------

bool testR3a()
{
  Utilities::title("Demonstrating Requirement #3a - creating DbElement");
  std::cout << "\n  Creating a db element with key \"Fawcett\":";

  // create database to hold std::string payload

  DbCore<std::string> db;
  DbProvider dbp;
  dbp.db() = db;

  // create some demo elements and insert into db

  DbElement<std::string> demoElem;

  demoElem.name("Jim");
  demoElem.descrip("Instructor for CSE687");
  demoElem.dateTime(DateTime().now());
  demoElem.payLoad("The good news is ...");

  if (demoElem.name() != "Jim")
    return false;
  if (demoElem.descrip() != "Instructor for CSE687")
    return false;
  if (demoElem.dateTime().now() != DateTime().now())
    return false;
  if (demoElem.payLoad() != "The good news is ...")
    return false;

  showHeader();
  showElem(demoElem);

  db["Fawcett"] = demoElem;
  dbp.db() = db;
  putLine();
  return true;
}
//----< demo second part of requirement #3 >---------------------------

bool testR3b()
{
  Utilities::title("Demonstrating Requirement #3b - creating DbCore");
  DbProvider dbp;
  DbCore<std::string> db = dbp.db();
  DbElement<std::string> demoElem = db["Fawcett"];
  demoElem.name("Ammar");
  demoElem.descrip("TA for CSE687");
  demoElem.payLoad("You should try ...");
  db["Salman"] = demoElem;
  if (!db.contains("Salman")) return false;
  demoElem.name("Jianan");
  demoElem.payLoad("Dr. Fawcett said ...");
  db["Sun"] = demoElem;
  demoElem.payLoad("You didn't demonstrate Requirement #4");
  demoElem.name("Nikhil");
  db["Prashar"] = demoElem;
  demoElem.payLoad("You didn't demonstrate Requirement #5");
  demoElem.name("Pranjul");
  db["Arora"] = demoElem;
  demoElem.payLoad("You didn't demonstrate Requirement #6");
  demoElem.name("Akash");
  db["Anjanappa"] = demoElem;
  if (db.size() != 6) return false;
  std::cout << "\n  after adding elements with keys: ";
  DbCore<std::string>::Keys keys = db.keys();
  showKeys(db); putLine();
  std::cout << "\n  make all the new elements children of element with key \"Fawcett\"";
  db["Fawcett"].children().push_back("Salman");
  db["Fawcett"].children().push_back("Sun");
  db["Fawcett"].children().push_back("Prashar");
  db["Fawcett"].children().push_back("Arora");
  db["Fawcett"].children().push_back("Anjanappa");
  showHeader(); showElem(db["Fawcett"]);
  db["Salman"].children().push_back("Sun");
  db["Salman"].children().push_back("Prashar");
  db["Salman"].children().push_back("Arora");
  db["Salman"].children().push_back("Anjanappa");

  // display the results
  putLine();
  std::cout << "\n  showing all the database elements:";
  showDb(db);
  putLine();
  std::cout << "\n  database keys are: ";
  showKeys(db);
  putLine();
  return true;
}

//----< Requirement 4 - Addition/Deletion of Element >-------------------------------

bool testR4() {
	Utilities::title("Demonstrating Requirement #4 - Addition/Deletion on DbElement");
	DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;
	DbElement<std::string> demoElem;
	demoElem.name("Ketul");
	demoElem.descrip("Student of CS");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("Database Testing");
	db.addtoDb("Mehta", demoElem);
	demoElem.name("Jatin");
	demoElem.descrip("Father of Ketul");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("Database Test1");
	db.addtoDb("Name", demoElem);
	showDb(db);
	std::cout<< "\n";
	db.deletefromDb("Name", demoElem);
	showDb(db);
	std::cout << "\n\n";
	return true;
}

//----< Requirement 5a - Updation of Element >-------------------------------

bool testR5a() {
	Utilities::title("Demonstrating Requirement #5a - Updating DbElement");
	DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;
	DbElement<std::string> demoElem;
	demoElem.name("Rahul");
	demoElem.descrip("Student of Computer Science");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("Database Testing");
	db.updateDb("Mehta", demoElem);
	showDb(db);
	std::cout << "\n\n";
	return true;
}

//----< Requirement 5b - Addition/Deletion of Element >-------------------------------

bool testR5b() {
	Utilities::title("Demonstrating Requirement #5b - Addition/Deletion of children");
	DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;
	DbElement<std::string> demoElem;
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

	db["Mehta"].children().push_back("Shah");
	db["Mehta"].children().push_back("Parekh");
	db["Mehta"].children().push_back("Maniyar");

	showDb(db);
	showElem(db["Mehta"]);
	std::cout << "\n\n";
	db.deletechild("Mehta", "Shah");
	showDb(db);
	return true;
}

//----< test stub >----------------------------------------------------

#ifdef TEST_DBCORE
using namespace Utilities;
int main()
{
  Utilities::Title("Testing DbCore - He said, she said database");
  putLine();
  TestExecutive ex;
  // define test structures with test function and message
  TestExecutive::TestStr ts1{ testR1, "Use C++11" };
  TestExecutive::TestStr ts2{ testR2, "Use streams and new and delete" };
  TestExecutive::TestStr ts3a{ testR3a, "Create DbElement<std::string>" };
  TestExecutive::TestStr ts3b{ testR3b, "Create DbCore<std::string>" };
  TestExecutive::TestStr ts4{ testR4, "Addition/Deletion on db " };
  TestExecutive::TestStr ts5a{ testR5a, "Updation on db " };
  TestExecutive::TestStr ts5b{ testR5b, "Addition/Deletion of Children " };
  // register test structures with TestExecutive instance, ex
  ex.registerTest(ts1);
  ex.registerTest(ts2);
  ex.registerTest(ts3a);
  ex.registerTest(ts3b);
  ex.registerTest(ts4);
  ex.registerTest(ts5a);
  ex.registerTest(ts5b);
  // run tests
  bool result = ex.doTests();
  if (result == true)
    std::cout << "\n  all tests passed";
  else
    std::cout << "\n  at least one test failed";
  putLine(2);
  return 0;
}
#endif
