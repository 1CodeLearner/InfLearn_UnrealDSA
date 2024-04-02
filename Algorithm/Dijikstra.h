#pragma once
#include <vector>
#include <iostream>
#include <list>

namespace Dijikstra
{
	using namespace std;
	struct Vertex
	{
		//data
	};

	vector<Vertex> vertices;
	vector<vector<int>> adjacent;

	void Initialize()
	{
		vertices.resize(6);
		adjacent.resize(6, vector<int>(6, -1));
		adjacent[0][1] = 15;
		adjacent[0][3] = 35;
		adjacent[1][0] = 15;
		adjacent[1][2] = 5;
		adjacent[1][3] = 10;
		adjacent[3][4] = 5;
		adjacent[5][4] = 5;
	}

	void Dijikstra_Practice2(int here) 
	{
		struct VertexCost 
		{
			int vertex;
			int bestCost;
		};

		list<VertexCost> discovered;
		vector<int> best(6, INT64_MAX);
		vector<int> parent;
		
		discovered.emplace_back(here, 0);
		best[here] = 0; 
		parent[here] = here;

		while (!discovered.empty()) {
			int findBestCost = INT64_MAX;
			list<VertexCost>::iterator bestIt;
			for (auto nextIt = discovered.begin(); nextIt != discovered.end(); ++nextIt) {
				if (nextIt->bestCost < findBestCost)
				{
					findBestCost = nextIt->bestCost;
					bestIt = nextIt; 
				}
			}

			here = bestIt->vertex;
			if(bestIt->bestCost >= best[here])
				continue;

			//loop through all vertex to find the next best cost node
			for (int there = 0; there < 6; there++) {
				if(adjacent[here][there] == -1)
					continue;
				int nextCost = adjacent[here][there];
				
				int bestCost = best[here] + nextCost;

				if(bestCost >= best[there])
					continue;
				
				discovered.push_back(VertexCost{there, bestCost});
				best[there] = bestCost;
				parent[there] = bestCost;
			}
		}
	}

	void Dijikstra_Practice(int here) 
	{
		using namespace std; 
		struct VertexCost 
		{
			int vertex; 
			int totalCost; // total cost relative to starting node
		};

		list<VertexCost> discovered;
		vector<int> best = vector<int>(6, INT64_MAX);
		vector<int> parent = vector<int>(6, -1);

		//starting node
		discovered.push_back(VertexCost{here, 0});
		best[here] = 0;
		parent[here] = here;

		while (!discovered.empty()) {
			int bestCost = INT64_MAX; 
			list<VertexCost>::iterator bestIter;
			for (auto bestIt = discovered.begin(); bestIt != discovered.end(); ++bestIt) {
				if (bestIt->totalCost < bestCost) {
					bestCost = bestIt->totalCost;
					bestIter = bestIt;
				}
			}

			//visit node
			here = bestIter->vertex;
			discovered.erase(bestIter);

			if(best[here] < bestIter->totalCost)
				continue;

			
			for (int there = 0; there < 6; ++there) {
				if(adjacent[here][there] == -1)
					continue;

				int nextCost = best[here] + adjacent[here][there];
				if(nextCost >= best[there])
					continue;
				
				discovered.push_back(VertexCost{there, nextCost});
				best[there] = nextCost; 
				parent[there] = here;
			}
		}
	}

	void Search(int here)
	{
		using namespace std;
		struct VertexCost
		{
			int vertex; //index of vertex 
			int cost; //total cost to travel to this vertex relative to the starting vertex
		};

		list<VertexCost> discovered; //Potential next node to travel from current node. One node Could have multiple VertexCosts.
		vector<int> best(6, INT32_MAX); // best path possible relative to starting node.
		vector<int> parent(6, -1);

		//starting node
		discovered.push_back(VertexCost{ here, 0 });
		best[here] = 0;

		while (!discovered.empty()) {
			list<VertexCost>::iterator bestIt;
			int bestCost = INT32_MAX;

			//find the best path 
			for (auto it = discovered.begin(); it != discovered.end(); it++) {
				if (it->cost < bestCost) {
					bestCost = it->cost;
					bestIt = it;
				}
			}

			//visit the node
			int cost = bestIt->cost;
			here = bestIt->vertex;
			discovered.erase(bestIt);

			//if best cost was already found at visited node
			if (best[here] < cost)
				continue;

			for (int there = 0; there < 6; there++) {
				if (adjacent[here][there])
					continue;

				int nextCost = best[here] + adjacent[here][there];
				if(nextCost >= best[there])
				continue; 

				discovered.push_back(VertexCost{there, nextCost});
				best[there] = nextCost;
				parent[there] = here;
			}
		}
	}
}

