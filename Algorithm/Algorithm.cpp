#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include "List.h"
#include "Vector.h"
#include "Stack.h"

using namespace std;

int main()
{
	//std::vector<int> v;
	//Vector<int> Test;

	//for (int i = 0; i < 100; ++i)
	//{
	//	Test.push_back(i);
	//	std::cout << Test[i] << " " << Test.size() << " " << Test.capacity() << std::endl;
	//}

	//Test.clear();
	//std::cout << Test.size() << " " << Test.capacity() << std::endl;

	
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
	//li.erase(eraseIt);
	//for (List<int>::iterator it = li.begin(); it != li.end(); ++it)
	//{
	//	std::cout << *it << " ";
	//}

	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	 
	s = (static_cast<Stack<int>&&>(s));
	

	while (!s.empty())
	{
		//최상위 원소
		int value = s.top();
		//최상위 원소 삭제
		s.pop();

		std::cout << value << " ";
	}

	int size = s.size();
	std::cout << size;
}