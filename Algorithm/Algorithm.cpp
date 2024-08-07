#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include "Queue.h"
#include "List.h"
#include "Vector.h"
#include "DFS.h"
#include "TestVector.h"
#include "TestList.h"
#include "TestStack.h"
#include "TestQueue.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "Tree.h"
#include "PriorityQueue.h"
#include "RedBlackTree.h"

using namespace std;

int main()
{

	/*RedBlackTree RBT;

	RBT.Insert(20);
	RBT.Insert(10);
	RBT.Insert(30);
	RBT.Insert(40);

	RBT.Delete(20);

	RBT.Print();*/


	/*Priority_queue<int, vector<int>, greater<int>> pq;

	pq.push(100);
	pq.push(300);
	pq.push(200);
	pq.push(500);
	pq.push(400);

	while (!pq.empty()) {
		int val = pq.top();
		pq.pop();
		cout << val << endl;
	}*/

	/*shared_ptr<Tree::Node> what = Tree::CreateTree();
	Tree::PrintTree(what, 0);
	cout << Tree::FindHeight(what);
	cout << endl;
	cout << Tree::FindHeightAlt(what);*/


	DFS::Init(false);
	DFS::SearchAll();

	//BFS::Init(true);
	//BFS::Search(0);

	/*Dijkstra::Initialize();
	Dijkstra::Practice2(0);*/


	//std::vector<int> v;
	//TestVector<int> Test;

	//for (int i = 0; i < 100; ++i)
	//{
	//	Test.push_back(i);
	//	std::cout << Test[i] << " " << Test.size() << " " << Test.capacity() << std::endl;
	//}

	//Test.clear();
	//std::cout << Test.size() << " " << Test.capacity() << std::endl;



	//TestList<int> li;
	//TestList<int>::iterator eraseIt;
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
	//li.insert(li.erase(eraseIt), 10); 
	//for(TestList<int>::iterator it = li.begin(); it != li.end(); ++it)
	//{
	//	cout << *it << endl;
	//}

	//TestStack<int> s;

	//s.push(1);
	//s.push(2);
	//s.push(3);

	//while (!s.empty()) 
	//{
	//	int data = s.top();
	//	s.pop();
	//}

	//int size = s.size();

	//int test = 10;


	TestQueue<int> q;

	for (int i = 0; i < 101; ++i)
	{
		q.push(i);
	}
	while (!q.empty())
	{
		int value = q.front();
		q.pop();
		//std::cout << value << endl;
	}
	int size = q.size();
	int test = 10;

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