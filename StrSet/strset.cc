#include <map>
#include <set>
#include <deque>
#include <cstring>
#include <assert.h>
#include <iostream>
#include "strset.h"
#include "strsetconst.h"

#ifdef DEBUG_
	const bool Debug = true;
#else
	const bool Debug = false;
#endif

typedef unsigned long ulong;
typedef std::map<ulong, std::set<std::string>> StrSet;

using namespace std;

/* Następny wolny indeks, który nie był jeszcze przydzielony */
ulong nextFree = 0;

/* Odwolanie sie do mapy zbiorów w celu zapobiegania Static Init Order Fiasco... */
StrSet& getSet()
{
	static StrSet strSet;// = new StrSet();
	return strSet;
}

/* Podaje wolny indeks */
ulong get_next_index()
{
		return nextFree++;
}

void inline sizeLog(ulong id)
{
	cerr << "size of " << id << ": " << strset_size(id) << endl;
}

ulong strset_new()
{
	if (Debug)
		cerr << "function: strset_new invoked" << endl;

	set<string> tmp;
	ulong ind = get_next_index();

	getSet().emplace(ind, tmp);

	if (Debug)
		cerr << "action: created strset with index " << ind << endl;

	return ind;
}

void strset_delete(ulong id)
{
	if (Debug)
		cerr << "function: strset_delete " << id << " invoked" << endl;
	if (id != strset42)
	{
		getSet().erase(id);

		if (Debug)
			cerr << "action: deleted " << id << endl;
	}
	else if (Debug)
		cerr << "!fatal action: trying to delete const strset42 " << endl;
}

size_t strset_size(ulong id)
{
	if (Debug)
		cerr << "function: strset_size " << id << " invoked " ;

	auto it = getSet().find(id);

	if (it == getSet().end())
	{
		if (Debug)
			cerr << "return: 0 ( not found " << id << "in map )" << endl;
		return 0;
	}
	else
	{
		if (Debug)
			cerr << "returned: " << it->second.size() << endl;
		return it->second.size();
	}

	return 0;
}

void strset_insert(ulong id, const char* value)
{
	if (Debug) 
	{
		if (value == NULL) {
			cerr << "!!!critical: trying to insert null into " << id << endl;
			return;
		}

		cerr << "function: strset_insert " << id << " " << value << " invoked" << endl;
	}

	/* zakladamy tutaj ze do strset42 mozemy dodać tylko "42" */
	if ((id != strset42) || ((id == strset42) && (value = "42")))
	{
		auto it = getSet().find(id);

		if (it != getSet().end())
		{
			it->second.emplace(string(value, strlen(value)));

			if (Debug)
			{
				cerr << "action: added " << value << "to strset " << id << endl;
				sizeLog(id);
			}
		}
		else if (Debug)
			cerr << "!fatal action: id of set not resolved" << endl;
	}
	else
	{
		if (Debug)
			cerr << "!fatal action: unable to add value to const strset42" << endl;
	}
}

void strset_remove(ulong id, const char* value)
{
	if (Debug)
	{
		if (value == NULL) {
			cerr << "!!!critical: trying to delete null from" << id << endl;
			return;
		}

		cerr << "function: strset_remove " << id << " " << value << " invoked" << endl;
	}

	if (id != strset42)
	{
		auto it = getSet().find(id);

		if (it != getSet().end())
		{
			it->second.erase(string(value, strlen(value)));
			if (Debug)
			{
				cerr << "action: removed " << value << "from strset " << id << endl;
				sizeLog(id);
			}
		}
	}
	else if (Debug)
		cerr << "!fatal action: unable to remove from const strset42" << endl;
}

int strset_test(ulong id, const char* value)
{
	if (Debug)
	{
		if (value == NULL) {
			cerr << "!!!critical: trying to test for null in " << id << endl;
			return 1;
		}
		cerr << "function: strset_remove " << id << " " << value << " invoked" << endl;
	}
	auto it = getSet().find(id);

	if (it != getSet().end())
	{
		if (it->second.find(string(value, strlen(value))) != it->second.end())
		{
			if (Debug)
				cerr << "return 1 (found) " << endl;
			return 1;
		}
	}

	if (Debug)
		cerr << "return 0 - (not found)" << endl;

	return 0;
}

void strset_clear(ulong id)
{
	if (Debug)
		cerr << "function: strset_clear " << id <<  " invoked" << endl;

	if (id != strset42)
	{
		auto it = getSet().find(id);

		if (it != getSet().end())
		{
			it->second.clear();

			if (Debug)
				cerr << "action: cleared" << id << endl;
		}
		else if (Debug)
			cerr << "!fatal action: unable to resolve id" << endl;
	}
	else if (Debug)
		cerr << "!fatal action: unable to clear const strset42" << endl;
}

/* Pomocnicza funkcja funkcji strset_comp */
int compare_existing(set<string> set1, set<string> set2)
{

	auto iter_second = set2.begin();

	for (auto iter = set1.begin(); iter != set1.end(); ++iter)
	{
		if (iter_second != set2.end())
		{
			if (*iter > *iter_second)
				return 1;
			else if (*iter < *iter_second)
				return -1;
			else
				++iter_second;
		}
		else
			return 1;
	}

	if (iter_second == set2.end())
		return 0;
	else
		return -1;
}

int strset_comp(ulong id1, ulong id2)
{
	if (Debug)
		cerr << "function: strset_comp" << id1 << " " << id2 << " invoked" << endl;

	auto set_p1 = getSet().find(id1);
	auto set_p2 = getSet().find(id2);

	set<string> empty_set, set1, set2;

	/* Sprawdzanie, czy zbiory o podanych nr ID istnieją, wpp tworzenie zbioru pustego */
	if (set_p1 == getSet().end())
	{
		set1 = empty_set;
		if (Debug)
			cerr << "log: set1 doesn't exist" << endl;
	}
	else
		set1 = set_p1->second;

	if (set_p2 == getSet().end())
	{
		set2 = empty_set;
		if (Debug)
			cerr << "log: set2 doesn't exist" << endl;
	}
	else
		set2 = set_p2->second;

	return compare_existing(set1, set2);
}
