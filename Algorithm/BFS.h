#pragma once
#include <vector>
#include <queue>
#include <iostream>

namespace BFS
{
	using namespace std;
	struct Vertex
	{
		//data	
	};
	vector<Vertex> vertices;

	vector<vector<int>> adjList;
	vector<vector<int>> adjMatrix;
	//vector<bool> visited;
	vector<bool> discovered;

	bool bList;

	void Init(bool bIsList)
	{
		vertices.resize(6);
		discovered.resize(6, false);
		//visited.resize(6, false);

		bList = bIsList;

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

	void Search(int here)
	{
		//visited[here] = true;
		queue<int> map;
		map.push(here);
		discovered[here] = true;

		while (!map.empty()) {
			here = map.front();
			map.pop();
			cout << "visited: " << here << endl;

			if (bList) {
				for (int i = 0; i < adjList[here].size(); ++i) {
					int there = adjList[here][i];
					if (discovered[there]) continue;
					map.push(there);
					discovered[there] = true;
				}
			}
			else{
				for(int i = 0; i < adjMatrix[here].size(); ++i){
					int there = adjMatrix[here][i];
					if(there == -1) continue;
					else there = i; 
					if(discovered[there]) continue; 
					map.push(there);
					discovered[there] = true;
				}
			}
		}
	}
}