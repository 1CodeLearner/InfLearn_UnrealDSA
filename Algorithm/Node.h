#pragma once


template<typename T>
struct Node
{
	Node()
		: _pNext(nullptr), _pPrev(nullptr), _value(T())
	{}
	Node(T value)
		: _pNext(nullptr), _pPrev(nullptr), _value(value)
	{}
	Node<T>* _pNext;
	Node<T>* _pPrev;
	T _value;
};