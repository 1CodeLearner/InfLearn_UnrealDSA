#pragma once
#include <iostream>
#include <vector>

namespace DFS
{
	using namespace std;

	struct Vertex
	{
		//Data
	};
	vector<DFS::Vertex> vertices;
	vector<vector<int>> adjacents;
	vector<bool> visited;

	void CreateGraph(int num = 6, bool bList = true)
	{
		if (bList)
		{
			vertices.resize(num);
			adjacents.resize(num);
			adjacents[0].push_back(1);
			adjacents[0].push_back(3);
			adjacents[1].push_back(0);
			adjacents[1].push_back(2);
			adjacents[1].push_back(3);
			adjacents[3].push_back(4);
			adjacents[5].push_back(4);

			visited.resize(num, false);
		}
		else
		{
			vertices.resize(num);
			adjacents.resize(num, vector<int>(6,-1));
			adjacents[0][1] = 1;
			adjacents[0][3] = 1;
			adjacents[1][0] = 1;
			adjacents[1][2] = 1;
			adjacents[1][3] = 1;
			adjacents[3][4] = 1;
			adjacents[5][4] = 1;

			visited.resize(num, false);
		}

	}

	void DFSTravel(int here, bool bList = true)
	{
		visited[here] = true;

		cout << "Traveled: " << here << endl;

		if (bList)
		{
			/*adjacent list*/
			for (int i = 0; i < adjacents[here].size(); ++i)
			{
				int there = adjacents[here][i];

				if (visited[there])
					continue;

				DFSTravel(there);
			}
		}
		else
		{
			/*adjacent matrix*/
			for (int i = 0; i < visited.size(); ++i)
			{
				if (adjacents[here][i] == -1)
					continue;
				if (!visited[i])
					DFSTravel(i, false);
			}
		}
	}
}