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
	}
	~List()
	{
		while (_pHead->_pNext != _pTail)
		{
			RemoveNode(_pTail->_pPrev);
		}
	}

	//List stuff
public:
	void push_back(T value)
	{
		AddNode(end(), value);
	}

	//Iterator stuff
public:
	using iterator = Iterator<T>;

	iterator end()
	{
		return iterator(_pHead->_pNext);
	}

	iterator begin()
	{
		return iterator(_pTail);
	}

	iterator insert(iterator it, T value)
	{
		return AddNode(it._pNode, value);
	}

private:
	iterator AddNode(iterator it, T value)
	{
		//Create new node
		Node<T>* newNode = new Node<T>(value);

		//Get current & previous nodes
		Node<T>* currNode = it._pNode;
		Node<T>* prevNode = currNode->_pPrev;

		//Set pointers for new node; 
		newNode->_pPrev = prevNode;
		newNode->_pNext = currNode;

		//Set pointer for existing nodes; 
		currNode->_pPrev = newNode;
		prevNode->_pNext = newNode;

		return iterator(newNode);
	}

	void RemoveNode(Node<T>* currNode)
	{
		//Get nodes that will reconnect
		Node<T>* prevNode = currNode->_pPrev;
		Node<T>* nextNode = currNode->_pNext;

		//Reconnect nodes
		prevNode->_pNext = nextNode;
		nextNode->_pPrev = prevNode;

		//Delete current node
		delete currNode;
	}

private:
	Node<T>* _pHead;
	Node<T>* _pTail;
};

