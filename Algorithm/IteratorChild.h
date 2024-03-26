#pragma once
#include "Iterator.h"
#include <iostream>

template<typename T>
class IteratorChild : public Iterator<T>
{
public:
	IteratorChild() = default;
	IteratorChild(Node<T>* node)
		: Iterator<T>(node)
	{}

	T& operator*() = delete; 
	//{
	//	std::cout << "Child Iterator";
	//	return this->_pNode->_value;
	//} 
};