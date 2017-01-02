#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <mutex>
#include <queue>

template <typename T>
class ConcurrentQueue
{
public:
	ConcurrentQueue();
	void push(T data);
	T pop();
	int size();
private:
	std::queue<T> conQueue;
	std::mutex queueMutex;
};

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
	T data = conQueue.front();
	conQueue.pop();
	queueMutex.unlock();
	return data;
}

template<typename T>
int ConcurrentQueue<T>::size()
{
	return conQueue.size();
}
#endif // !CONCURRENT_QUEUE_H

