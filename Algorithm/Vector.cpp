#include "Vector.h"

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