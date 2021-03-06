

/////////////////////////////////////////////////////////////////////
// DbCore.h - Implements NoSql database prototype                  //
// ver 1.0                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides two classes:
* - query_condition class stores the regex value for every DbElement
*   It contains fields for name, description, datetime and child
* - query class defines functions of vaiorus queries to be applied on DbElement.

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



#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../DateTime/DateTime.h"
#include <functional>
#include <regex>
#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"


namespace NoSqlDb
{
	/////////////////////////////////////////////////////////////////////
	// query_condition class
	// - Stores the regex value for every DbElement

	class query_condition
	{
	public:
		using Key = std::string;
		using Children = std::vector<Key>;

		query_condition();

		query_condition& name(std::string name);
		std::string name() const;

		query_condition& descript(std::string descript);
		std::string descript() const;

		query_condition& key(std::string key);
		std::string key() const;

		//----< Class Members >-------------------------------

	private:
		std::string name_regex;
		std::string descript_regex;
		std::string key_regex;
		Children children_regex;
	};

	query_condition::query_condition()
	{
		name_regex = "(.*)";
		descript_regex = "(.*)";
		key_regex = "(.*)";
	}

	//----< Getter/Setter Methods for query_condition class >-------------------------------

	typename query_condition& query_condition::name(std::string name)
	{
		name_regex = name;
		return *this;
	}

	typename std::string query_condition::name() const
	{
		return name_regex;
	}

	query_condition& query_condition::descript(std::string descript)
	{
		descript_regex = descript;
		return *this;
	}

	std::string query_condition::descript() const
	{
		return descript_regex;
	}

	query_condition& query_condition::key(std::string key)
	{
		key_regex = key;
		return *this;
	}

	std::string query_condition::key() const
	{
		return key_regex;
	}

	//----< Query class >-------------------------------
	// - Functions for Query operations.

	template<typename P>
	class Query {
		using Key = std::string;
		using Keys = std::vector<Key>;
	public:
		Query(DbCore<P>& db) : db_{ db } { db_ = db; keys_ = db_.keys(); }
		Query& select(const query_condition& cond);
		Query& from(const Keys& keys) { keys_ = keys; return *this; }
		Query& operation_OR(Query<P>& q);
		Query& operation_AND(Query<P>& q);
		Query& child(Key k);
		void show();
		Keys keys() { return keys_; }
		void date_info(DateTime date_first, DateTime date_second);
		bool satisfy(Key, const query_condition& cond);

	private:
		//----< Class Members >-------------------------------
		DbCore<P>& db_;
		Keys keys_;
	};
	
	//----< Query for selecting element through key >-------------------------------

	template <typename P>
	Query<P>& Query<P>::select(const query_condition& cond)
	{
		Keys temp;
		for (auto it : keys_)
		{
			if (satisfy(it, cond))
			{
				temp.push_back(it);
			}
		}
		keys_ = temp;
		return *this;
	}

	//----< Query for satisfy function >-------------------------------
	template <typename P>
	bool Query<P>::satisfy(Key key, const query_condition& cond)
	{
		std::regex x1(cond.name());
		std::regex x2(cond.descript());
		std::regex x3(cond.key());
		if (std::regex_match(db_[key].name(), x1) && std::regex_match(db_[key].descrip(), x2) && std::regex_match(key, x3))
			return true;
		return false;
	}

	//----< Query to display Date Time information >-------------------------------
	template <typename P>
	void Query<P>::date_info(DateTime date_first, DateTime date_second)
	{
		for (unsigned int i = 0; i < keys_.size(); i++) {
			DateTime date_third = db_[keys_[i]].dateTime();
			if (date_first.operator > (date_third) && date_second.operator < (date_third)) {
				std::cout << std::endl << "Key : " << keys_[i] << "\t" << "Name : " << db_[keys_[i]].name() << "\t" << "Description : " << db_[keys_[i]].descrip();
			}
		}
	}

	//----< Query performing OR operation >-------------------------------
	template <typename P>
	Query<P>& Query<P>::operation_OR(Query<P>& q)
	{
		Keys v2 = q.keys();

		for (unsigned int i = 0; i < v2.size(); i++)
		{
			unsigned int j;
			for (j = 0; j < keys_.size(); j++)
			{
				//std::cout << "V1 :" << v1[i] << " V2 :" << v2[j]<<" \n";
				if (v2[i] == keys_[j])
				{
					break;
				}
			}
			if (j == keys_.size())
				keys_.push_back(v2[i]);
		}
		return *this;
	}

	//----< Query performing AND operation >-------------------------------
	template <typename P>
	Query<P>& Query<P>::child(Key k)
	{
		from(db_[k].children());
		return *this;
	}

	template <typename P>
	Query<P>& Query<P>::operation_AND(Query<P>& q)
	{
		Keys v1 = keys_;
		Keys v2 = q.keys();
		Keys v;

		for (unsigned int i = 0; i < v1.size(); i++)
		{
			for (unsigned int j = 0; j < v2.size(); j++)
			{
				if (v1[i] == v2[j])
				{
					v.push_back(v2[j]);
				}
			}
		}
		keys_ = v;
		return *this;
	}

	//----< Display Function >-------------------------------
	// - Show function to display the element satisfying the queries.
	template <typename P>
	void Query<P>::show()
	{
		NoSqlDb::showHeader();
		for (unsigned int i = 0; i < keys_.size(); i++) {
			NoSqlDb::showElem(db_[keys_[i]]);
		}

	}
}