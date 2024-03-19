#include <iostream>
#include <vector>
#include <list>
#include "List.h"
#include "Vector.h"

using namespace std;

int main()
{
	//std::vector<int> v;
	Vector<int> Test;
	
	for (int i = 0; i < 100; ++i)
	{
		Test.push_back(i);
		std::cout << Test[i] << " " << Test.size() << " " << Test.capacity() << std::endl;
	}

	Test.clear();
	std::cout << Test.size() << " " << Test.capacity() << std::endl;

	
	/*List<int> li;
	List<int>::iterator eraseIt;
	for(int i = 0; i < 2; ++i)
	{
		if(i==5)
		{
			eraseIt = li.insert(li.end(), i);
		}
		else
		{
			li.push_back(i);
		}
	}*/

	//for (List<int>::iterator it = li.begin(); it != li.end(); ++it)
	//{
	//	li.erase(eraseIt);
	//}
	
}