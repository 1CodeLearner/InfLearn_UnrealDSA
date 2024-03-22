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

	Node<T>* _pNode;

	//++it
	Iterator& operator++(const Iterator& other)
	{
		_pNode = _pNode->_pNext;
		return _pNode; 
	}

};

