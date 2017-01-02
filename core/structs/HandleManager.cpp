#include "HandleManager.h"

#include <cstddef>
#include "../exceptions/HandleManagerException.h"

HandleManager::HandleEntry::HandleEntry()
{
	counter = 1;
	active = 0;
	listEnd = 0;
	entry = NULL;
}

HandleManager::HandleEntry::HandleEntry(uint32 nextFreeIndex)
{
	nextFreeIndex = nextFreeIndex;
	counter = 1;
	active = 0;
	listEnd = 0;
	entry = NULL;
}

HandleManager::HandleManager()
{
	reset();
}

void HandleManager::reset()
{
	activeEntryCount = 0;
	firstFreeIndex = 0;

	for (int i = 0; i < MAX_ENTRIES - 1; ++i)
	{
		entries[i] = HandleEntry(i + 1);
	}
	entries[MAX_ENTRIES - 1] = HandleEntry();
	entries[MAX_ENTRIES - 1].listEnd = true;
}

/**
* Attempts to modify the next free handle entry.
* @param *p		pointer to an entry
* @param type	the type of the entry
* @return	a valid handle with the specified pointer and type
*/
Handle HandleManager::add(void* p, uint32 type)
{
	if (activeEntryCount >= MAX_ENTRIES - 1)
		throw(HandleManagerException());
	if (type < 0 || type > 31)
		throw(HandleManagerException());

	const int newIndex = firstFreeIndex;
	if (newIndex > MAX_ENTRIES ||
		entries[newIndex].active == true ||
		entries[newIndex].listEnd)
		throw(HandleManagerException());

	firstFreeIndex = entries[newIndex].nextFreeIndex;
	entries[newIndex].counter += 1;
	entries[newIndex].active = true;
	entries[newIndex].entry = p;

	++activeEntryCount;

	return Handle(newIndex, entries[newIndex].counter, type);
}

/**
* Updates the given handle to posess the given entry pointer.
* @param handle	Handle object to modify
* @param *p		Pointer for an entry for the handle entry to contain.
*/
void HandleManager::update(Handle handle, void* p)
{
	const int index = handle.index;
	// Assert entries[index].counter == counter: These must be equal
	// to be sure that we are accessing a valid handle.
	if (entries[index].counter != handle.counter)
		return;
	// Assert that the index is active. This must be true to
	// be sure that we are accessing a valid handle.
	if (!entries[index].active)
		return;
	entries[index].entry = p;
}

/**
* Renders the given handle inactive, saves the state of the
* next free index, and marks its index as the first free index.
* @param handle	Handle object to remove from the handle manager.
*/
void HandleManager::remove(const Handle handle)
{
	const uint32 index = handle.index;
	// Assert entries[index].counter == counter: These must be equal
	// to be sure that we are accessing a valid handle.
	if (entries[index].counter != handle.counter)
		return;
	// Assert that the index is active. This must be true to
	// be sure that we are accessing a valid handle.
	if (!entries[index].active)
		return;
	entries[index].nextFreeIndex = firstFreeIndex;
	entries[index].active = 0;
	firstFreeIndex = index;

	--activeEntryCount;
}

/**
* Attempts to return the pointer of a specific handle.
* @param handle	
* @return NULL	if the pointer could not be safely returned.
*         p		else a pointer to the handle's entry.
* @see get(const Handle handle, void*& out) const;
*/
void* HandleManager::get(Handle handle) const
{
	void* p = NULL;
	if (!get(handle, p))
		return NULL;
	return p;
}

/**
* Attempts to get the pointer of the specified handle.
* @param handle	
* @param *&out	
* @return false	if the handle's index is inactive or its
*				counter is not equal to the counter of its index.
		  true	if out is now pointing to the correct entry
*/
bool HandleManager::get(const Handle handle, void*& out) const
{
	const int index = handle.index;
	if (entries[index].counter != handle.counter ||
		entries[index].active == false)
		return false;
	out = entries[index].entry;
	return true;
}

int HandleManager::getCount() const
{
	return activeEntryCount;
}