#pragma once
#include <vector>

void CreateGraph_1()
{
	using namespace std;

	struct Vertex
	{
		vector<Vertex*> edges;
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// Q) 0번 -> 3번 정점이 연결되어 있나요?
	bool connected = false;
	for (Vertex* edge : v[0].edges)
	{
		if (edge == &v[3])
		{
			connected = true;
			break;
		}
	}
}

void CreateGraph_2()
{
	using namespace std;

	struct Vertex
	{
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리
	// adjacent[n] -> n번째 정점과 연결된 정점 목록
	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// 정점이 100개
	// - 지하철 노선도 -> 서로 드문 드문 연결 (양옆, 환승역이라면 조금 더 ++)
	// - 페이스북 친구 -> 서로 빽빽하게 연결

	// Q) 0번 -> 3번 정점이 연결되어 있나요?
	bool connected = false;
	for (int vertex : adjacent[0])
	{
		if (vertex == 3)
		{
			connected = true;
			break;
		}
	}

	// STL
	vector<int>& adj = adjacent[0];
	bool connected2 = (std::find(adj.begin(), adj.end(), 3) != adj.end());
}


void CreateGraph_3()
{
	using namespace std;

	struct Vertex
	{
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리
	// [X][O][X][O][X][X]
	// [O][X][O][O][X][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]

	// 읽는 방법 : adjacent[from][to]
	// 행렬을 이용한 그래프 표현 (2차원 배열)
	// 메모리 소모가 심하지만, 빠른 접근이 가능하다
	// (간선이 많은 경우 이점이 있다)
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// Q) 0번 -> 3번 정점이 연결되어 있나요?
	bool connected = adjacent[0][3];

	vector<vector<int>> adjacent2(6, vector<int>(6, -1));
	adjacent2[0][1] = 15;
	adjacent2[0][3] = 35;
	adjacent2[1][0] = 3;
	adjacent2[1][2] = 68;
	adjacent2[1][3] = 57;
	adjacent2[3][4] = 10;
	adjacent2[5][4] = 5;
}