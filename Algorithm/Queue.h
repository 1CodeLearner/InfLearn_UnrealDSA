#pragma once
#include <vector>

template<typename T>
class Queue
{
public:
	Queue()
	{
		v.resize(100);
	}
	void push(T val);
	void pop();
	int size() const;
	bool empty() const;
	T& front();
private:
	std::vector<T> v;

	int _front;
	int _back;
	int _size;
};

template<typename T>
inline void Queue<T>::push(T val)
{
	//if is full: return
	if (_size == v.size())
		return;
	//if not full: push value onto v

	v[_size] = val;
	_back = (_back + 1) % v.size();
	_size++;
}

template<typename T>
inline void Queue<T>::pop()
{
	if (!empty())
		_front = (_front + 1) % v.size();
	_size--;
}

template<typename T>
inline int Queue<T>::size() const
{
	return _size;
}

template<typename T>
inline bool Queue<T>::empty() const
{
	return _size == 0;
}

template<typename T>
inline T& Queue<T>::front()
{
	return v[_front];
}
