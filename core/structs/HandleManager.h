#ifndef HANDLE_MANAGER_H
#define HANDLE_MANAGER_H

#include "Handle.h"

class HandleManager
{
public:
	static const int MAX_ENTRIES = 4096;

	HandleManager();

	void reset();
	Handle add(void* p, uint32 type);
	void update(Handle handle, void* p);
	void remove(Handle handle);

	void* get(Handle handle) const;
	bool get(Handle handle, void*& out) const;
	template<typename T> bool getAs(Handle handle, T& out) const;

	int getCount() const;

private:
	HandleManager(const HandleManager&);

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

	HandleEntry entries[MAX_ENTRIES];
	int activeEntryCount;
	uint32 firstFreeIndex;
};

template<typename T>
inline bool HandleManager::getAs(Handle handle, T& out) const
{
	void* outAsVoid;
	const bool rv = get(handle, outAsVoid);
	out = union_cast<T>(outAsVoid);
	
	return rv;
}

#endif // !HANDLE_MANAGER_H
