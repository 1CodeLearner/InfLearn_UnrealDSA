#pragma once
#include <vector>
#include <iostream>
#include <list>

namespace Dijkstra
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

	void Practice(int here) 
	{
		using namespace std; 
		struct VertexCost 
		{
			int vertex; 
			int cost; // most efficient cost relative to starting node
			bool operator==(const VertexCost& other) {
				return vertex == other.vertex && cost == other.cost;
			}
		};

		vector<VertexCost> discovered;
		vector<int> bestCost = vector<int>(6, INT32_MAX);
		vector<int> parent = vector<int>(6, -1);

		discovered.push_back({here, 0});
		bestCost[here] = 0;
		//parent[here] = here;

		while (!discovered.empty()) {
			vector<VertexCost>::iterator bestIt;
			int tempBestCost = INT32_MAX;

			//Find best possible route in current node
			for (auto it = discovered.begin(); it != discovered.end(); ++it) {
				if (it->cost < tempBestCost) {
					tempBestCost = it->cost;
					bestIt = it;
				}
			}
			
			//visit the next best possible node
			here = bestIt->vertex;
			int cost = bestIt->cost;

			//remove the next best possible node from discovered
			auto newEnd = std::remove(discovered.begin(), discovered.end(), *bestIt);
			discovered.erase(newEnd, discovered.end());
			
			//continue if next best possible route was already found
			if(cost > bestCost[here])
				continue;

			//loop through all possible routes in current node
			for (int there = 0; there < 6; ++there) {
				//skip if route doesn't exist
				if(adjacent[here][there] == -1)
					continue;
				
				//get the cost of next node and check if a best possible route was already found for it
				int nextCost = bestCost[here] + adjacent[here][there];
				if(nextCost >= bestCost[there])
					continue;
				//else
				
				bestCost[there] = nextCost;

				//store the next potential best possible node to discovered
				discovered.push_back({ there, nextCost });
				parent[there] = here;
			}
		}

		for (int i = 0; i < bestCost.size(); ++i) {
			cout << "Node " << i << ": " << bestCost[i] << endl;
		}
		for (int i = 0; i < parent.size(); ++i) {
			cout << "Node " << i << ": " << parent[i] << endl;
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
				if (adjacent[here][there] == -1)
					continue;

				int nextCost = best[here] + adjacent[here][there];
				if(nextCost >= best[there])
				continue; 

				discovered.push_back(VertexCost{there, nextCost});
				best[there] = nextCost;
				parent[there] = here;
			}
		}

		for (int i = 0; i < best.size(); ++i) {
			cout << "Node " << i << ": " << best[i] << endl;
		}
		for (int i = 0; i < parent.size(); ++i) {
			cout << "Node " << i << ": " << parent[i] << endl;
		}
	}
}

