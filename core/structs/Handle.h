#ifndef HANDLE_H
#define HANDLE_H

typedef unsigned int uint32;

struct Handle
{
	Handle() : index(0), counter(0), type(0)
	{}
	Handle(uint32 index, uint32 counter, uint32 type)
	{
		this->index = index;
		this->counter = counter;
		this->type = type;
	}

	inline operator uint32() const;
	

	uint32 index;
	uint32 counter;
	uint32 type;
};

Handle::operator uint32() const
{
	return type << 27 | counter << 12 | index;
}

#endif // !HANDLE_H