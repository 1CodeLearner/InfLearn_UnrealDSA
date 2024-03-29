#pragma once
#include <vector>
#include <list>
#include "Node.h"

template<typename T>
class TestStack 
{
public: 
	void push(T val) {
		l.push_back(val);
	}

	bool empty() {
		return l.empty();
	}

	T& top() {
		return l.back();
	}

	void pop() {
		l.pop_back();
	}

	int size() {
		return l.size();
	}


private: 
	std::list<T> l;
};

//template<typename T>
//class TestStack
//{
//public:
//	TestStack()
//		: _size(0), topPtr(nullptr)
//	{}
//	~TestStack() {
//		while (!empty()) {
//			pop();
//		}
//		topPtr = nullptr;
//	}
//
//	void push(T val) {
//		Node<T>* newNode = new Node<T>(val);
//		if (!empty()) {
//			newNode->_pNext = topPtr;
//		}
//		topPtr = newNode;
//		_size++;
//	}
//
//	bool empty() {
//		return !topPtr;
//	}
//
//	T& top() {
//		return topPtr->_value;
//	}
//
//	void pop() {
//		Node<T>* temp = topPtr;
//		topPtr = topPtr->_pNext;
//		delete temp;
//		_size--;
//	}
//
//	int size() {
//		return _size;
//	}
//protected:
//private:
//	Node<T>* topPtr;
//	int _size;
//};

//template<typename T>
//class TestStack
//{
//	
//public:
//	TestStack() {};
//	
//	void push(T val) {
//		v.push_back(val);
//	}
//
//	bool empty() {
//		return v.empty();
//	}
//
//	T& top() {
//		return v.back();
//	}
//
//	void pop() {
//		v.pop_back();
//	}
//
//	int size() {
//		return v.size();
//	}
//
//private:
//	std::vector<T> v;
//};
