#pragma once
#include <iostream>
#include <vector>

namespace DFS
{
	using namespace std;

	bool bList;

	//vertex
	struct Vertex
	{
		//data
	};
	vector<Vertex> vertices;

	//adjacents
	vector<vector<int>> adjList;
	vector<vector<int>> adjMatrix;
	vector<bool> visited;

	void Init(bool bUseList = true)
	{
		bList = bUseList;

		vertices.resize(6);
		visited.resize(6, false);

		if (bList) {
			adjList.resize(6);
			adjList[0].push_back(1);
			adjList[1].push_back(2);
			adjList[1].push_back(5);
			adjList[2].push_back(3);
			adjList[2].push_back(5);
			adjList[4].push_back(3);
			adjList[4].push_back(5);
			adjList[5].push_back(4);
		}
		else {
			adjMatrix.resize(6, vector<int>(6, -1));
			adjMatrix[0][1] = 1;
			adjMatrix[1][2] = 1;
			adjMatrix[1][5] = 1;
			adjMatrix[2][3] = 1;
			adjMatrix[2][5] = 1;
			adjMatrix[4][3] = 1;
			adjMatrix[4][5] = 1;
			adjMatrix[5][4] = 1;
		}
	}

	void Search(int here) {
		visited[here] = true;

		cout << "Visited " << here << endl;

		if(bList){
			for(int i = 0; i < adjList[here].size(); ++i){
				int there = adjList[here][i];
				if(visited[there]) continue;
				Search(there);
			}
		}
		else{
			for(int i = 0; i < adjMatrix[here].size(); ++i){
				int there = adjMatrix[here][i];
				if(there == -1) continue; 
				else there = i;
				if(visited[there]) continue;
				Search(there);
			}
		}
	}
}


//namespace DFS
//{
//	using namespace std;
//
//	struct Vertex
//	{
//		//Data
//	};
//	vector<DFS::Vertex> vertices;
//	vector<vector<int>> adjacents;
//	vector<bool> visited;
//
//	void CreateGraph(int num = 6, bool bList = true)
//	{
//		if (bList)
//		{
//			vertices.resize(num);
//			adjacents.resize(num);
//			adjacents[0].push_back(1);
//			adjacents[0].push_back(3);
//			adjacents[1].push_back(0);
//			adjacents[1].push_back(2);
//			adjacents[1].push_back(3);
//			adjacents[3].push_back(4);
//			adjacents[5].push_back(4);
//
//			visited.resize(num, false);
//		}
//		else
//		{
//			vertices.resize(num);
//			adjacents.resize(num, vector<int>(6,-1));
//			adjacents[0][1] = 1;
//			adjacents[0][3] = 1;
//			adjacents[1][0] = 1;
//			adjacents[1][2] = 1;
//			adjacents[1][3] = 1;
//			adjacents[3][4] = 1;
//			adjacents[5][4] = 1;
//
//			visited.resize(num, false);
//		}
//
//	}
//
//	void DFSTravel(int here, bool bList = true)
//	{
//		visited[here] = true;
//
//		cout << "Traveled: " << here << endl;
//
//		if (bList)
//		{
//			/*adjacent list*/
//			for (int i = 0; i < adjacents[here].size(); ++i)
//			{
//				int there = adjacents[here][i];
//
//				if (visited[there])
//					continue;
//
//				DFSTravel(there);
//			}
//		}
//		else
//		{
//			/*adjacent matrix*/
//			for (int i = 0; i < visited.size(); ++i)
//			{
//				if (adjacents[here][i] == -1)
//					continue;
//				if (!visited[i])
//					DFSTravel(i, false);
//			}
//		}
//	}
//}