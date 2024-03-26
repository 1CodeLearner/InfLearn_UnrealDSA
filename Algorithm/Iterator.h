#pragma once
#include "Node.h"
#include <iostream>

template<typename T>
class Iterator
{
public:
	Iterator()
		: _pNode(nullptr)
	{}

	Iterator(Node<T>* node)
		: _pNode(node)
	{}

	//it + val
	Iterator& operator+(int index)
	{
		
	}

	//++it
	Iterator& operator++() 
	{
		_pNode = _pNode->_pNext;
		return * this;
	}
	//it++
	Iterator operator++(int)
	{
		Iterator<T> temp = *this; 
		_pNode = _pNode->_pNext;
		return temp;
	}
	
	//--it
	Iterator& operator--() 
	{
		_pNode = _pNode->_prev;
		return *this;
	}
	//it--
	Iterator operator--(int)
	{
		Iterator<T> temp = *this; 
		_pNode = _pNode->_pNext;
		return temp;
	}
	//*it
	T& operator*()
	{
		return _pNode->_value;
	}

	bool operator==(const Iterator& other)
	{
		return _pNode == other._pNode;
	}

	bool operator!=(const Iterator& other)
	{
		return _pNode != other._pNode;
	}

public:
	Node<T>* _pNode;
};

