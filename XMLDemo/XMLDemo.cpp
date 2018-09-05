/////////////////////////////////////////////////////////////////////
// Operations.cpp -  Satisfying the requirement by inserting valus to XMLDocument from Database and Reverse.//
// ver 1.0																									//
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Operations :
*---------------
* Three functions are defined in the file as :
* - makeDb creates the databse and enter the elements to the database.
* - testR8a satifies the requirement by creating XMLDocument from the values of Database.
* - testR8b satifies the requirement by creating Databse from XMLDocument.
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <fstream>
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
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

using namespace XmlProcessing;

//----< Requirement 8a - Persist collection of database element to XML file by keys >-------------------------------

bool testR8a()
{
	DbProvider dbp;
	NoSqlDb::DbCore<std::string> db = dbp.db();

	Utilities::title("Demonstrating Requirement #8a - Persist collection of database element to XML file by keys ");
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
	NoSqlDb::DbCore<std::string> db; DbProvider dbp; dbp.db() = db;

	Utilities::title("Demonstrating Requirement #8b - Creating Database from XMLDOcument ");
	std::cout << "\n  Building Database from XmlDocument";
	std::cout << "\n ----------------------------------";
	using Key = std::string;
	using Sptr = std::shared_ptr<AbstractXmlElement>;
	std::ifstream ifs("output.xml");
	std::string Xml((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	XmlDocument newXDoc(Xml, XmlDocument::str);
	std::vector<Sptr> records = newXDoc.descendents("dbRecord").select();
	for (auto pRecord : records)
	{
		Key key;
		NoSqlDb::DbElement<std::string> elem;
		std::vector<Sptr> pChildren = pRecord->children();
		for (auto pChild : pChildren) {
			// record's children are key and value
			if (pChild->tag() == "key") {
				// get value of TextElement child
				key = pChild->children()[0]->value(); }
			else {
				// value represents a MockDbElem with children name and description
				std::vector<Sptr> pValueChildren = pChild->children();
				for (auto pValueChild : pValueChildren) {
					if (pValueChild->tag() == "name") {
						// get value of TextElement child
						elem.name(pValueChild->children()[0]->value()); 
					}
					if (pValueChild->tag() == "description"){
						// get value of TextElement child
						elem.descrip(pValueChild->children()[0]->value()); }
				}
			}
		}
		db[key] = elem;
	}
	NoSqlDb::showDb(db);
	std::cout << "\n\n";
	return true;
}

#ifdef TEST_XMLDEMO

int main()
{
	makeDb();
	testR8a();
	testR8b();
	return 0;
}
#endif