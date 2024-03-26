#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "Queue.h"
#include "List.h"
#include "Vector.h"
#include "DFS.h"

using namespace std;

int main()
{

	DFS::CreateGraph(6, false);
	DFS::DFSTravel(0, false);


	////std::vector<int> v;
	//Vector<int> Test;
	//
	//for (int i = 0; i < 100; ++i)
	//{
	//	Test.push_back(i);
	//	std::cout << Test[i] << " " << Test.size() << " " << Test.capacity() << std::endl;
	//}

	//Test.clear();
	//std::cout << Test.size() << " " << Test.capacity() << std::endl;
	//Test[10];

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
	// 
	//for(List<int>::iterator it = li.begin(); it != li.end(); ++it)
	//{
	//	//li.erase(eraseIt);
	//}

	/*Queue<int> q;

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
	std::cout << size << endl;*/

	/*int value = 10;
	int value2 = 10;
	int what = value++ + 15;
	int what2 = ++value2 + 15;

	cout << what << '\n';
	cout << what2;

	std::vector<int> test;
	std::list<int> test2;
	std::vector<int>::iterator it = test.begin();
	std::list<int>::iterator it2 = test2.begin();*/
}