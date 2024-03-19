#pragma once
#include <iostream>

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
{

}

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