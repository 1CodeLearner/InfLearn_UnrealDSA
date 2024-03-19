#pragma once
#include "Node.h"

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

	/*Iterator operator=(const Iterator& other)
		: _pNode(other._pNode)
	{}*/

	T operator*()
	{
		return _pNode->_value;
	}

public:
	Node<T>* _pNode;
};

