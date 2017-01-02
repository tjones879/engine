#ifndef HANDLE_ENTRY_H
#define HANDLE_ENTRY_H

#include "Handle.h"

struct HandleEntry
{
	HandleEntry();
	explicit HandleEntry(uint32 nextFreeIndex);

	uint32 nextFreeIndex : 12;
	uint32 counter : 15;
	uint32 active : 1;
	uint32 listEnd : 1;
	void* entry;
};



#endif // !HANDLE_ENTRY_H