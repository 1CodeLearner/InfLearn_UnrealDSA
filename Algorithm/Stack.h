#pragma once
#include <iostream>

template<typename T>
class Stack
{
public:
	Stack();
	Stack(const Stack& other)
	{
		*this = other;
		//operator=(other);
	}
	Stack& operator=(const Stack& other) 
	{
		if (this != &other) 
		{
			std::cout << "Copied!";

			Clear();

			Node<T>* otherNode = other._head;
			Stack<T> tempStack;

			//fill up temporary stack
			while (otherNode)
			{
				tempStack.push(otherNode->_value);
				otherNode = otherNode->_next;
			}

			//fill up stack for this object
			while (!tempStack.empty()) 
			{
				push(tempStack.top());
				tempStack.pop();
			}
		}
		return *this;
	}
	
	Stack(Stack&& other) noexcept
		: _head(other._head)
	{
		std::cout << "moved!";
		other._head = nullptr;
	}
	
	Stack& operator=(Stack&& other) 
	{
		if (this != &other) 
		{
			std::cout << "moved!";
			_head = other._head;
			other._head = nullptr;
		}
		else 
		{
			std::cout << "Failed!";

		}
		return *this;
	}


	~Stack();

	void push(T value);

	bool empty() const;

	T& top() const;

	void pop();

	int size() const;

private:
	template<typename T>
	struct Node
	{
		Node()
			: _next(nullptr), _value(T())
		{}
		Node(T value)
			: _next(nullptr), _value(value)
		{}
		Node<T>* _next;
		T _value;
	};

	inline void Clear() 
	{
		while (!empty())
		{
			pop();
		}
		_head = nullptr;
	}

	Node<T>* _head;
};

template<typename T>
Stack<T>::Stack()
	: _head(nullptr)
{}

template<typename T>
inline Stack<T>::~Stack()
{
	Clear();
}

template<typename T>
bool Stack<T>::empty() const
{
	return _head == nullptr;
}

template<typename T>
inline T& Stack<T>::top() const
{
	return _head->_value;
}

template<typename T>
inline void Stack<T>::pop()
{
	if (!empty()) 
	{
		Node<T>* temp = _head;
		_head = _head->_next;
		delete temp;
	}
}

template<typename T>
inline int Stack<T>::size() const
{
	const Node<T>* temp = _head;
	int counter = 0; 
	while (temp != nullptr) 
	{
		temp = temp->_next;
		counter++;
	}
	return counter;
}

template<typename T>
void Stack<T>::push(T value)
{
	Node<T>* newNode = new Node<T>(value);

	if (empty())
	{
		_head = newNode;
	}
	else 
	{
		newNode->_next = _head; 
		_head = newNode;
	}
}