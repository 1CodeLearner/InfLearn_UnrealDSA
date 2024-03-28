#pragma once
#include "Iterator.h"

template<typename T>
class TestList
{
public:
	TestList()
		: _head(nullptr), _tail(nullptr)
	{
		_head = new Node<T>(T());
		_tail = new Node<T>(T());
		_head->_pNext = _tail;
		_tail->_pPrev = _head;
	};

	~TestList() 
	{
		while (!empty()) 
		{
			erase(begin());
		}
		delete _head;
		delete _tail;
	}

	bool empty() 
	{
		return _head->_pNext == _tail && _tail->_pPrev == _head;
	}

	void push_back(T val) 
	{
		insert(end(), val);
	}

public:
	using iterator = Iterator<T>;

	iterator erase(iterator it) 
	{
		//get current node
		Node<T>* curr = it._pNode;
		
		//get next node
		Node<T>* next = curr->_pNext;

		//get previous node
		Node<T>* prev = curr->_pPrev;

		//connect next and previous nodes
		next->_pPrev = prev;
		prev->_pNext = next;

		//disconnect next and prev nodes
		curr->_pNext = nullptr;
		curr->_pPrev = nullptr;
		
		//return current node
		return iterator(curr);

	}

	iterator insert(iterator it, T val)
	{
		//get previous node
		Node<T>* prev = it._pNode->_pPrev;
		//get current node
		Node<T>* curr = it._pNode;

		//create new node
		Node<T>* newNode = new Node<T>(val);

		//attach existing nodes to new node
		prev->_pNext = newNode;
		curr->_pPrev = newNode;

		//attach new node to existing nodes
		newNode->_pNext = curr;
		newNode->_pPrev = prev;

		//return new node
		return iterator(newNode);
	}

	iterator end() 
	{
		return iterator(_tail);
	}

	iterator begin() 
	{
		return iterator(_head->_pNext);
	}

private:
	Node<T>* _head;
	Node<T>* _tail;
};