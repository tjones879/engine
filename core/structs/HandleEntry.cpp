#include "HandleEntry.h"
#include <cstddef>

HandleEntry::HandleEntry()
{
	counter = 1;
	active = 0;
	listEnd = 0;
	entry = NULL;
}

HandleEntry::HandleEntry(uint32 nextFreeIndex)
{
	nextFreeIndex = nextFreeIndex;
	counter = 1;
	active = 0;
	listEnd = 0;
	entry = NULL;
}