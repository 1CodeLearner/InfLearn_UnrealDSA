#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "Queue.h"
#include "List.h"

using namespace std;

template<typename T>
class Vector
{
public:
	Vector(int size = 0);
	~Vector();
	void push_back(T value);
	inline int size() const { return _size; }
	inline int capacity() const { return _capacity; }
	void clear();
	T& operator[](int index) 
	{
		return _dataPtr[index];			
	}
private:
	int _size;
	int _capacity;
	T* _dataPtr;
	static constexpr float growthScale = 1.5;
	T* GetNewMemory()
	{
		if (_capacity == 0)
		{
			_capacity = 1;
		}
		_capacity = (int)std::ceil(_capacity * growthScale);

		return new T[_capacity];
	}


};

template<typename T>
Vector<T>::Vector(int size /*= 0*/)
	: _size(size), _capacity(size* growthScale), _dataPtr(new T[_capacity])
{}

template<typename T>
Vector<T>::~Vector()
{
	delete[] _dataPtr;
	_dataPtr = nullptr;
}


template<typename T>
void Vector<T>::clear()
{
	for (int i = 0; i < _size; ++i)
	{
		_dataPtr[i] = T();
	}
	_size = 0; 
}

template<typename T>
void Vector<T>::push_back(T value)
{
	if (!_dataPtr)
	{
		_dataPtr = GetNewMemory();
	}
	if (_size == _capacity)
	{
		T* temp = _dataPtr;
		_dataPtr = GetNewMemory();
		for (int i = 0; i < size(); ++i)
		{
			_dataPtr[i] = temp[i];
		}
		delete[] temp;
	}

	_dataPtr[_size] = value;
	_size++;
}

int main()
{
	/*std::vector<int> v;
	vector<int> Test;
	
	for (int i = 0; i < 100; ++i)
	{
		Test.push_back(i);
		std::cout << Test[i] << " " << Test.size() << " " << Test.capacity() << std::endl;
	}

	Test.clear();
	std::cout << Test.size() << " " << Test.capacity() << std::endl;
	Test[10];*/
	
	//List<int> li;
	//List<int>::iterator eraseIt;
	//for(int i = 0; i < 10; ++i)
	//{
	//	if(i==5)
	//	{
	//		eraseIt = li.insert(li.end(), i);
	//	}
	//	else
	//	{
	//		li.push_back(i);
	//	}
	//}

	//for(list<int>::iterator it = li.begin(); it != li.end(); ++it)
	//{
	//	//li.erase(eraseIt);
	//}

	Queue<int> q; 

	for (int i = 0; i < 101; ++i) 
	{
		q.push(i);
	}
	while (!q.empty()) 
	{
		int value = q.front();
		q.pop();
		std::cout << value << endl;
	}
	int size = q.size();
	std::cout << size << endl;
}