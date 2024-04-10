#pragma once
#include <vector>
#include <functional>
#include <iostream>

template<typename T, typename U = std::vector<T>, typename V = std::less<T>>
class Priority_queue
{

public:
	void push(T val)
	{
		v.push_back(val);

		int curr = int(v.size() - 1);
		int parent = (curr - 1) / 2;

		while (parent >= 0 && parent < v.size()) {
			if (less(v[parent], v[curr])) {
				std::swap(v[curr], v[parent]);
				curr = parent;
				parent = (curr - 1) / 2;
			}
			else break;
		}
	}

	bool empty()
	{
		return v.empty();
	}

	T& top()
	{
		return v[0];
	}

	void pop()
	{
		std::swap(v[0], v.back());
		v.pop_back();

		int curr = 0;
		int left = curr * 2 + 1;
		int right = curr * 2 + 2;

		while (IsValid(left) || IsValid(right))
		{
			if (IsValid(left) && IsValid(right))
			{
				int child = 0;
				if (less(v[left], v[right])) child = left;
				else child = right;

				if (less(v[curr], v[child])) {
					std::swap(v[curr], v[child]);
					curr = child;
				}
				else break;
			}
			else
			{
				if (less(v[curr], v[left])) {
					std::swap(v[curr], v[left]);
					curr = left;
				}
				else break;
			}

			left = curr * 2 + 1;
			right = curr * 2 + 2;
		}
	}

private:
	U v;
	V less;
	bool IsValid(int index) {
		return index >= 0 && index < v.size();
	}
};