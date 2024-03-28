#pragma once
#include <assert.h>
#include "Iterator.h"

template<typename T>
class TestVector
{
public:
	TestVector()
		: _size(0), _capacity(0), _dataPtr(nullptr)
	{}
	~TestVector()
	{
		delete[] _dataPtr;
	}

	int size() { return _size; }
	int capacity() { return _capacity; }
	void clear()
	{
		delete[] _dataPtr;
		_dataPtr = new T[_capacity];
		_size = 0;
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < _size);
		return _dataPtr[index];
	}

	void push_back(T val)
	{
		if (!_dataPtr)
		{
			_dataPtr = GetMoreCapacity();
		}
		if (_size == _capacity)
		{
			T* temp = _dataPtr;
			_dataPtr = GetMoreCapacity();
			for (int i = 0; i < _size; ++i)
			{
				_dataPtr[i] = temp[i];
			}
			delete[] temp;
		}
		_dataPtr[_size] = val;
		_size++;
	}

private:
	int _size;
	int _capacity;
	T* _dataPtr;

	T* GetMoreCapacity()
	{
		_capacity *= 2;
		_capacity = std::max(1, _capacity);
		T* temp = new T[_capacity];
		return temp;
	}
};