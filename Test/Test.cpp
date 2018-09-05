#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test.cpp - includes the definition of main function wherein all the Test functions are called.      //
// ver 1.0																							   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018										   //
////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
* Package Operations:
* -------------------
* This package
*/

#include "Test.h"


// Testing Function

void func1() {

	TestExecutive ex;

	testR1();
	testR2();
	testR3a();
	testR3b();

	// define test structures with test function and message

	TestExecutive::TestStr ts1{ testR1, "Use C++11" };
	TestExecutive::TestStr ts2{ testR2, "Use streams and new and delete" };
	TestExecutive::TestStr ts3a{ testR3a, "Create DbElement<std::string>" };
	TestExecutive::TestStr ts3b{ testR3b, "Create DbCore<std::string>" };

	// register test structures with TestExecutive instance, ex

	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(ts3a);
	ex.registerTest(ts3b);
}

void func2() {

	TestExecutive ex;

	testR4();
	testR5a();
	testR5b();

	// define test structures with test function and message

	TestExecutive::TestStr ts4{ testR4, "Addition/Deletion on db " };
	TestExecutive::TestStr ts5a{ testR5a, "Updation on db " };
	TestExecutive::TestStr ts5b{ testR5b, "Addition/Deletion of Children " };

	// register test structures with TestExecutive instance, ex

	ex.registerTest(ts4);
	ex.registerTest(ts5a);
	ex.registerTest(ts5b);
}

void func3() {

	TestExecutive ex;

	testR6();
	testR7();
	testR8a();
	testR8b();

	// define test structures with test function and message

	TestExecutive::TestStr ts6{ testR6, "Supporting Queries " };
	TestExecutive::TestStr ts7{ testR7, "Supporting AND/OR Operations " };
	TestExecutive::TestStr ts8a{ testR8a, "Persist collection of elements from Database to XMLDocument" };
	TestExecutive::TestStr ts8b{ testR8b, "Creating Databse from XML file" };

	// register test structures with TestExecutive instance, ex

	ex.registerTest(ts6);
	ex.registerTest(ts7);
	ex.registerTest(ts8a);
	ex.registerTest(ts8b);

}

#ifdef TEST_TEST

int main()
{

	func1();
	func2();
	func3();

	return 0;
}
#endif