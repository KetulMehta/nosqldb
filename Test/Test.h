#pragma once

/////////////////////////////////////////////////////////////////////
// DbCore.h - Implements NoSql database prototype                  //
// ver 1.0                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package includes all the test functions according to the given requirements.

* Required Files:
* ---------------
* query.h, Query.cpp
* DbCore.h, Dbcore.cpp
* DateTime.h, DateTime.cpp
* Utilities.h, Utilities.cpp
*
*
* Maintenance History:
* --------------------
* ver 1.1 : 19 Jan 2018
* - added code to throw exception in index operators if input key is not in database
* ver 1.0 : 10 Jan 2018
* - first release
*/

#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include <iostream>
#include <iomanip>
#include <functional>
#include "../Query/query.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <fstream>
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"



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

//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
{
	Utilities::putline(n, out);
};

//----< Function to create Database >-------------------------------

void makeDb()
{
	NoSqlDb::DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;
	NoSqlDb::DbElement<std::string> demoElem;
	demoElem.name("Ketul");
	demoElem.descrip("Student of Computer Science");
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
	dbp.db() = db;
}


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

	NoSqlDb::DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;

	// create some demo elements and insert into db

	NoSqlDb::DbElement<std::string> demoElem;

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

	NoSqlDb::showHeader();
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
	DbProvider dbp; NoSqlDb::DbCore<std::string> db = dbp.db();
	NoSqlDb::DbElement<std::string> demoElem = db["Fawcett"];
	demoElem.name("Ammar");
	demoElem.descrip("TA for CSE687");
	demoElem.payLoad("You should try ...");
	db["Salman"] = demoElem;
	if (!db.contains("Salman"))
		return false;
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
	if (db.size() != 6) { return false; }
	std::cout << "\n  after adding elements with keys: ";
	NoSqlDb::DbCore<std::string>::Keys keys = db.keys();
	showKeys(db);
	putLine();
	std::cout << "\n  make all the new elements children of element with key \"Fawcett\"";
	db["Fawcett"].children().push_back("Salman");
	db["Fawcett"].children().push_back("Sun");
	db["Fawcett"].children().push_back("Prashar");
	db["Fawcett"].children().push_back("Arora");
	db["Fawcett"].children().push_back("Anjanappa");
	NoSqlDb::showHeader();
	showElem(db["Fawcett"]);
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
	Utilities::title("\n  Demonstrating Requirement #4 - Addition/Deletion on DbElement");
	NoSqlDb::DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;
	NoSqlDb::DbElement<std::string> demoElem;
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
	std::cout << "\n";
	db.deletefromDb("Name", demoElem);
	showDb(db);
	std::cout << "\n\n";
	return true;
}

//----< Requirement 5a - Updation of Element >-------------------------------

bool testR5a() {
	Utilities::title("\n  Demonstrating Requirement #5a - Updating DbElement");
	NoSqlDb::DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;
	NoSqlDb::DbElement<std::string> demoElem;
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
	Utilities::title("\n  Demonstrating Requirement #5b - Addition/Deletion of children");
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

//----< Requirement 6 - Suppporting Queries >-------------------------------

bool testR6()
{
	makeDb();
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

//----< Requirement 7 - Suppporting AND/OR Operations. >-------------------------------

bool testR7()
{
	DbProvider dbp;
	NoSqlDb::DbCore<std::string> db = dbp.db();
	showDb(db);
	Utilities::title("\n  Demonstrating Requirement #7 - Supporting AND/OR operations.\n");
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

using namespace XmlProcessing;

//----< Requirement 8a - Persist collection of database element to XML file by keys >-------------------------------

bool testR8a()
{
	DbProvider dbp;
	NoSqlDb::DbCore<std::string> db = dbp.db();

	Utilities::title("\n  Demonstrating Requirement #8a - Persist collection of database element to XML file by keys ");
	std::cout << "\n  Demonstrating Persistance with XmlDocument";
	std::cout << "\n =================================================\n";
	std::cout << "\n    version 1.1 adds attribute handling\n";

	std::cout << "\n  Building Database";
	std::cout << "\n ------------------------";

	std::cout << "\n  Creating XML representation of Databse using XmlDocument";
	std::cout << "\n ----------------------------------------------------------------";

	using Sptr = std::shared_ptr<AbstractXmlElement>;
	Sptr pDb = makeTaggedElement("db");
	pDb->addAttrib("type", "testDb");
	Sptr pDocElem = makeDocElement(pDb);
	XmlDocument xDoc(pDocElem);

	for (auto item : db)
	{
		Sptr pRecord = makeTaggedElement("dbRecord");
		pDb->addChild(pRecord);
		Sptr pKey = makeTaggedElement("key", item.first);
		pRecord->addChild(pKey);

		Sptr pValue = makeTaggedElement("value");
		pRecord->addChild(pValue);
		Sptr pName = makeTaggedElement("name", item.second.name());
		pValue->addChild(pName);
		Sptr pDescrip = makeTaggedElement("description", item.second.descrip());
		pValue->addChild(pDescrip);
		Sptr pPL = makeTaggedElement("payload", item.second.payLoad());
		pValue->addChild(pPL);

	}
	std::string Xml = xDoc.toString();
	std::cout << Xml << std::endl;

	std::cout << "\n  Creating XmlDocument from XML string";
	std::cout << "\n --------------------------------------";
	std::ofstream out("output.xml");
	out << Xml;
	out.close();
	return true;
}

//----< Requirement 8b - Creating Databse from XML file>-------------------------------

bool testR8b()
{
	NoSqlDb::DbCore<std::string> db;
	DbProvider dbp;
	dbp.db() = db;
	Utilities::title("\n  Demonstrating Requirement #8b - Creating Database from XMLDOcument ");
	std::cout << "\n  Building Databse from XmlDocument";
	std::cout << "\n ----------------------------------";
	using Key = std::string;
	using Sptr = std::shared_ptr<AbstractXmlElement>;
	std::ifstream ifs("output.xml");
	std::string Xml((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	XmlDocument newXDoc(Xml, XmlDocument::str);
	std::vector<Sptr> records = newXDoc.descendents("dbRecord").select();
	for (auto pRecord : records){ Key key;
		NoSqlDb::DbElement<std::string> elem;
		std::vector<Sptr> pChildren = pRecord->children();
		for (auto pChild : pChildren){
			// record's children are key and value
			if (pChild->tag() == "key"){
				// get value of TextElement child
				key = pChild->children()[0]->value(); }
			else{
				// value represents a MockDbElem with children name and description
				std::vector<Sptr> pValueChildren = pChild->children();
				for (auto pValueChild : pValueChildren){
					if (pValueChild->tag() == "name") {
						// get value of TextElement child
						elem.name(pValueChild->children()[0]->value());
					}
					if (pValueChild->tag() == "description") {
						// get value of TextElement child
						elem.descrip(pValueChild->children()[0]->value());
					}
					if (pValueChild->tag() == "payload") {
						// get value of TextElement child
						elem.payLoad(pValueChild->children()[0]->value());
					}
				}
			}
		}
		db[key] = elem;
	}
	NoSqlDb::showDb(db);
	std::cout << "\n\n";
	return true;
}
