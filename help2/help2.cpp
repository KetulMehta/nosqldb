// help2.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>

class CC
{
public:
  CC & take(const std::string& s)
  {
    s_ = s;
    return *this;
  }
  CC& show()
  {
    std::cout << "\n  " << s_;
    return *this;
  }
private:
  std::string s_;
};
int main()
{
  CC cc1;
  cc1.take("first string").show().take("second string").show();
  std::cout << "\n\n";
    return 0;

    // DbCore<P> db;
    // Query q1(db);
    //   Query instances hold a reference to a database and a vector of keys;
    //   When constructed those keys are db.keys()

    // Conditions conds1;
    // conds1.name(re1).author(re2).description(re3);
    //   Conditions instances hold a DbElement<P>;
    //   the re1, ... terms are regular expressions

    // q1.select(conds1).show();
    //    select uses conds1 DbElement parts to match db elements for each q1 key
    //    and when done replaces its original keys with the new key set

    // Query q2(db);
    // Conditions conds2;
    // conds2.date(atimedate);
    // q2.from(q1.keys()).select(conds2).show();
    //   from replaces q2's keys with q1's keys

    // This design also allows us to do this:
    // Query q3(db);
    // q3.select(conds1).select(cond2).show();

    // We might want to make specialized selectors for common queries:
    // q3.selectName(re1).selectAuthor(re2).show();

    // class Query
    // {
    // public:
    //   Query(const DbCore<P>& db) : db_(db) {}
    //   Query& select(const Conditions& cond);
    //   Query& from(Keys& keys);
    //   void show();
    //   Keys keys();
    //
    //   more stuff for you to supply
    // private:
    //   DbCore<P>& db_
    //   Keys keys_;
    // };
}
 
