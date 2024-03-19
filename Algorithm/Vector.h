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
