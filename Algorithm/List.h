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

	iterator end(){ return iterator(_pTail); }

	iterator begin() { return iterator(_pHead->_pNext); }

	iterator insert(iterator it, T value)
	{
		Node<T>* newNode = AddNode(it._pNode, value);
		return iterator(newNode);
	}

	iterator erase(iterator it) 
	{
		return iterator(RemoveNode(it._pNode));
	}

private:
	Node<T>* AddNode(Node<T>* pCurr, T value);

	Node<T>* RemoveNode(Node<T>* pCurr);

private:
	Node<T>* _pHead;
	Node<T>* _pTail;
};

template<typename T>
Node<T>* List<T>::AddNode(Node<T>* pCurr, T value)
{
	//create new node
	Node<T>* newNode = new Node<T>(value);

	//Get pointer to previous node
	Node<T>* pPrev = pCurr->_pPrev;

	//connect new node to existing nodes, previous and current
	newNode->_pNext = pCurr;
	newNode->_pPrev = pPrev;

	//Connect existing nodes to new node
	pPrev->_pNext = newNode;
	pCurr->_pPrev = newNode;

	//return new node
	return newNode;
}

template<typename T>
inline Node<T>* List<T>::RemoveNode(Node<T>* pCurr)
{
	//get next and prev nodes
	Node<T>* next = pCurr->_pNext;
	Node<T>* prev = pCurr->_pPrev;

	//reconnect next and prev nodes
	next->_pPrev = prev;
	prev->_pNext = next;

	//delete current node
	delete pCurr;

	//return ptr to next node
	return next;
}
