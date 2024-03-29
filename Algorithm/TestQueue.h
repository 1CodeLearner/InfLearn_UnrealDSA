#pragma once
#include <list>
#include <vector>

template<typename T>
class TestQueue
{
public:
	TestQueue()
		: _head(0), _tail(0), _size(0)
	{
	}

	void push(T val) {
		if (_size == v.size()) {
			int newSize = std::max(1, _size * 2);
			std::vector<T> newV(newSize);
			for (int i = 0; i < v.size(); ++i) {
				newV[i] = v[(_head + i) % v.size()];
			}
			_head = 0;
			_tail = _size;
			v.swap(newV);
		}
		v[_tail] = val;
		_tail = ++_tail % v.size();
		_size++;
	}
	bool empty() {
		return _head == _tail && _size == 0;
	}
	T& front() {
		assert(_size != 0);
		return v[_head];
	}
	void pop() {
		if (!empty()) {
			_head = (_head + 1) % v.size();
			_size--;
		}
	}
	int size() {
		return _size;
	}

private:
	std::vector<T> v;
	int _head;
	int _tail;
	int _size;
};

//template<typename T>
//class TestQueue 
//{
//public:
//	void push(T val) {
//		l.push_back(val);
//	}
//	bool empty() {
//		return l.empty();
//	}
//	T& front() {
//		return l.front();
//	}
//	void pop() {
//		l.pop_front(); 
//	}
//	int size() {
//		return l.size();
//	}
//private:
//	std::list<T> l;
//};