#include "ConcurrentQueue.h"

template<typename T>
ConcurrentQueue<T>::ConcurrentQueue()
{
	
}

template<typename T>
void ConcurrentQueue<T>::push(T data)
{
	queueMutex.lock();
	conQueue.push(data);
	queueMutex.unlock();
}

template<typename T>
T ConcurrentQueue<T>::pop()
{
	queueMutex.lock();
	T data = conQueue[0];
	conQueue.pop();
	queueMutex.unlock();
	return data;
}

template<typename T>
int ConcurrentQueue<T>::size()
{
	return conQueue.size();
}
