#include "strsetconst.h"
#include "strset.h"
#include <iostream>

unsigned long create42();

extern const unsigned long strset42 = create42();

unsigned long create42()
{
	unsigned long tmp = strset_new();
	strset_insert(tmp, "42");
	return tmp;
}