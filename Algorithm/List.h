#pragma once
#include "Iterator.h"

template<typename T>
class List
{
public:
	List()
		:_pHead(new Node<T>), _pTail(new Node<T>)
	{
		_pHead->_pNext = _pTail;
		_pTail->_pPrev = _pHead;

		_pHead->_pPrev = nullptr;
		_pTail->_pNext = nullptr;
	}

public:
	void push_back(T value)
	{
		AddNode(end()._pNode, value);
	}

public:
	using iterator = Iterator<T>;

	iterator end()
	{
		return iterator(_pTail);
	}

	iterator begin()
	{
		return iterator(_pHead->_pNext);
	}

	iterator insert(iterator it, T value)
	{
		Node<T>* newNode = AddNode(it._pNode, value);
		return iterator(newNode);
	}

private:
	Node<T>* AddNode(Node<T>* pCurr, T value)
	{
		//create new node
		Node<T>* newNode = new Node<T>(value);

		//Get pointer to previous node
		Node<T>* pPrev = pCurr->_pPrev;

		//connect new node to existing nodes, previous and current
		newNode->_pNext = pCurr;
		newNode->_pPrev = pPrev;

		//Connect existing nodes to new node
		pPrev->_pNext = pCurr;
		pCurr->_pPrev = pCurr;

		//return new node
		return newNode;
	}


private:
	Node<T>* _pHead;
	Node<T>* _pTail;
};