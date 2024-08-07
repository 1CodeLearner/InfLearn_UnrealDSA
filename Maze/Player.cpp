﻿#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
	_board = board;
	if (_board)
	{
		_loc = _board->GetStartPos();
	}

	//RightHandRule();
	//BFS();
	//AStar();
	//AStarExample();
	MoreAStar();
}

void Player::Update(uint64 deltaTime)
{
	if (index >= absLocs.size())
		return;
	totalTime += deltaTime;
	if (totalTime >= maxTime && !AtDestination())
	{
		_loc = absLocs[index];
		index++;
		totalTime = 0;
	}
}

bool Player::CanMove(Pos newPos) const
{
	TileType tileType = _board->GetTileType(newPos);
	bool bCanMove = false;
	switch (tileType)
	{
	case TileType::EMPTY:
		bCanMove = true;
		break;
	case TileType::WALL:
		bCanMove = false;
		break;
	}
	return bCanMove;
}

bool Player::AtDestination() const
{
	Pos wat = _loc;
	return  wat == _board->GetEndPos();
}

void Player::RightHandRule()
{
	Pos tempPos = _loc;
	Pos dest = _board->GetEndPos();

	Pos dir[4]
	{
		Pos{-1,0}, //up
		Pos{0,-1},	//left
		Pos{1,0},	//down
		Pos{0,1}	//right
	};

	//Right-hand rule
	//¿ì¼ö¹ý
	while (tempPos != dest)
	{
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		//1.ÇöÀç ¹Ù¶óº¸´Â ¹æÇâÀ» ±âÁØÀ¸·Î ¿À¸¥ÂÊÀ¸·Î °¥ ¼ö ÀÖ´ÂÁö È®ÀÎ
		if (CanMove(tempPos + dir[newDir]))
		{
			//¿À¸¥ÂÊ ¹æÇâÀ¸·Î 90µµ È¸Àü
			_dir = newDir;
			//¾ÕÀ¸·Î ÇÑ º¸ ÀüÁø
			tempPos += dir[newDir];
			absLocs.push_back(tempPos);
		}
		else if (CanMove(tempPos + dir[_dir]))
		{
			//¾ÕÀ¸·Î ÇÑ º¸ ÀüÁø
			tempPos += dir[_dir];
			absLocs.push_back(tempPos);
		}
		else
		{
			//¿ÞÂÊ ¹æÇâÀ¸·Î 90µµ È¸Àü.
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	stack<Pos> s;

	for (int i = 0; i < absLocs.size() - 1; i++)
	{
		//pop off duplicate paths.
		if (s.empty() == false && s.top() == absLocs[i + 1])
			s.pop();
		/*
		push in unique paths.
		duplicate paths that lead to destination are pushed back in.
		*/
		else
			s.push(absLocs[i]);
	}

	//push final destination
	if (absLocs.empty() == false)
		s.push(absLocs.back());

	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	std::reverse(path.begin(), path.end());

	absLocs = path;
}

void Player::BFS()
{
	using namespace std;

	Pos tempPos = _loc;
	Pos dest = _board->GetEndPos();

	Pos dir[4]
	{
		Pos{-1,0}, //up
		Pos{0,-1},	//left
		Pos{1,0},	//down
		Pos{0,1}	//right
	};

	queue<Pos> q;
	vector<vector<bool>> discovered(_board->GetSize(), vector<bool>(_board->GetSize(), false));
	//vector<vector<Pos>> parent(_board->GetSize(), vector<Pos>(_board->GetSize(), Pos(-1, -1)));
	map<Pos, Pos> parent;

	q.push(tempPos);
	discovered[tempPos.y][tempPos.x] = true;
	//parent[tempPos.y][tempPos.x] = tempPos;
	parent[tempPos] = tempPos;

	Pos visitedPos;
	while (!q.empty()) {
		//get visited position
		visitedPos = q.front();
		q.pop();

		//break out if end position is visited
		if (visitedPos == _board->GetEndPos())
			break;

		for (int32 i = 0; i < 4; ++i) {
			//get potential direction
			Pos newDir = visitedPos + dir[i];

			//if that new path is blocked, continue
			if (!CanMove(newDir)) continue;

			//check if direction was already visited
			if (discovered[newDir.y][newDir.x]) continue;

			//if it wasn't visited, push that sucker in the queue
			q.push(newDir);
			discovered[newDir.y][newDir.x] = true;
			//parent[newDir.y][newDir.x] = visitedPos;
			parent[newDir] = visitedPos;
		}
	}

	//push in end position
	absLocs.push_back(visitedPos);

	//back-track until start position is reached
	while (visitedPos != _board->GetStartPos()) {
		//get parent of current node
		//const Pos& prev = parent[visitedPos.y][visitedPos.x];
		const Pos& prev = parent[visitedPos];

		absLocs.push_back(prev);
		visitedPos = prev;
	}

	//Get path
	reverse(absLocs.begin(), absLocs.end());
}

struct MoreNode
{
	MoreNode(){}
	MoreNode(int _f, int _g, int _h, Pos _pos)
		:f(_f), g(_g), h(_h), pos(_pos)
	{}
	int f;
	int g;
	int h;
	Pos pos = { 0,0 };

	bool operator>(const MoreNode& other) const
	{
		if (f == other.f) return h > other.h;
		return f > other.f;
	}

	bool operator<(const MoreNode& other) const
	{
		if (f == other.f) return h < other.h;
		return f < other.f;
	}
};

void Player::MoreAStar()
{
	Pos Start = _board->GetStartPos();
	Pos End = _board->GetEndPos();

	priority_queue<MoreNode, vector<MoreNode>, greater<MoreNode>> pq;
	vector<vector<int>> best(_board->GetSize(), vector<int>(_board->GetSize(), INT_MAX));
	vector<vector<Pos>> parent(_board->GetSize(), vector<Pos>(_board->GetSize()));

	Pos dirMove[] =
	{
		{0, -1},
		{-1, 0},
		{0, 1},
		{1, 0}
	};

	int dirCost[] =
	{
		10,
		10,
		10,
		10
	};

	int g = 0;
	int h = 10 * abs(Start.y - End.x) + abs(Start.x - End.y);
	int f = g + h;
	MoreNode node(f, g, h, Start);

	pq.push(node);
	best[node.pos.x][node.pos.y] = f;
	parent[node.pos.x][node.pos.y] = Start;

	while (pq.size() != 0)
	{
		MoreNode here = pq.top();
		pq.pop();
		Pos herePos = here.pos;

		if (best[herePos.x][herePos.y] < here.f) continue;

		for (int i = 0; i < DIR_COUNT; ++i)
		{
			Pos NextPos = herePos + dirMove[i];
			if (!CanMove(NextPos)) continue;

			g = here.g + dirCost[i];
			h = 10 * abs(NextPos.x - End.x) + abs(NextPos.y - End.y);
			f = g + h;

			if (best[NextPos.x][NextPos.y] < f) continue;

			best[NextPos.x][NextPos.y] = f;
			parent[NextPos.x][NextPos.y] = herePos;
			MoreNode Next(f, g, h, NextPos);
			pq.push(Next);
		}
	}

	Pos curPos = End;
	absLocs.push_back(curPos);

	while (Start != curPos)
	{
		absLocs.push_back(parent[curPos.x][curPos.y]);
		curPos = parent[curPos.x][curPos.y];
	}

	reverse(absLocs.begin(), absLocs.end());
}

struct Node
{
	bool operator<(const Node& other) const {
		return f < other.f;
	}
	bool operator>(const Node& other) const {
		return f > other.f;
	}
	int32 f = 0;
	int32 g = 0;
	Pos pos = { 0,0 };
};

void Player::AnotherAStarPractice() 
{
	struct TileFound 
	{
		bool operator<(const TileFound& other) const {
			return f < other.f;
		}
		bool operator>(const TileFound& other) const {
			return f > other.f;
		}
		int f = 0; 
		int g = 0;	
		Pos pos{0, 0};
	};
	
	enum
	{
		MAXDIR = 4
	};

	Pos dir[]
	{
		Pos{-1,0}, //up
		Pos{0,-1},	//left
		Pos{1,0},	//down
		Pos{0,1},	//right
		Pos{1,1},
		Pos{1,-1},
		Pos{-1,1},
		Pos{-1,-1}
	};

	int cost[]
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};

	//i need to determine my starting and ending point
	Pos startPos = _loc; 
	Pos endPos = _board->GetEndPos();
	
	//next i need to declare necessary containers
	map<Pos, int> bestCost;
	map<Pos, Pos> parent;
	priority_queue<TileFound, vector<TileFound>, greater<TileFound>> discovered;

	//i need to initialize the containers
	//find f g and h
	int g = 0, h = 10 * (abs(startPos.y - endPos.y) + abs(startPos.x - endPos.x));
	bestCost[startPos] = g + h;
	parent[startPos] = startPos;
	discovered.push(TileFound{g + h, g, startPos});

	while (!discovered.empty()) 
	{
		TileFound curr = discovered.top();
		discovered.pop();

	}
}

void Player::AStarExample()
{
	enum MaxDir
	{
		MAXDIR = 4
	};

	Pos dir[]
	{
		Pos{-1,0}, //up
		Pos{0,-1},	//left
		Pos{1,0},	//down
		Pos{0,1},	//right
		Pos{1,1},
		Pos{1,-1},
		Pos{-1,1},
		Pos{-1,-1}
	};

	int cost[]
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};

	Pos start = _board->GetStartPos();
	Pos end = _board->GetEndPos();
	int size = _board->GetSize();
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));
	vector<vector<bool>> closed(size, vector<bool>(size, false));
	map<Pos, Pos> parent;
	priority_queue<Node, vector<Node>, greater<Node>> pq;

	//best[start.y][start.x] = 0;
	parent[start] = start;
	int32 g = 0;
	int32 h = 10 * (abs(start.y - end.y) + abs(start.x - end.x));
	pq.push(Node{g + h, g, start});

	while (!pq.empty())
	{
		Node curr = pq.top();
		pq.pop();

		Pos currPos = curr.pos;

		if (currPos == end) break;

		if (best[currPos.y][currPos.x] < curr.f)
			continue;

		closed[currPos.y][currPos.x] = true;

		for (int i = 0; i < MAXDIR; ++i)
		{
			Pos nextPos = currPos + dir[i];

			if (!CanMove(nextPos))
				continue;

			g = curr.f + cost[i];
			h = 10 * (abs(nextPos.y - end.y) + abs(nextPos.x - end.x));

			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			if(closed[nextPos.y][nextPos.x])
				continue;

			best[nextPos.y][nextPos.x] = g + h;
			parent[nextPos] = currPos;
			Node next(Node{ g + h, g, nextPos });
			pq.push(next);
		}
	}

	Pos tempPos = end;
	absLocs.push_back(tempPos);

	while (tempPos != start)
	{
		absLocs.push_back(parent[tempPos]);
		tempPos = parent[tempPos];
	}
	reverse(absLocs.begin(), absLocs.end());
}

struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int32	f; // f = g + h
	int32	g;
	Pos		pos;
};

void Player::AStar()
{
	// 점수 매기기
	// F = G + H
	// F = 최종 점수 (작을 수 록 좋음, 경로에 따라 달라짐)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을 수록 좋음, 경로에 따라 달라짐) 
	// H = 목적지에서 얼마나 가까운지 (작을 수록 좋음, 고정)

	Pos start = _loc;
	Pos dest = _board->GetEndPos();

	enum
	{
		DIR_COUNT = 8
	};

	Pos front[] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
		Pos {-1, -1},	// UP_LEFT
		Pos {1, -1},	// DOWN_LEFT
		Pos {1, 1},		// DOWN_RIGHT
		Pos {-1, 1},	// UP_RIGHT
	};

	int32 cost[] =
	{
		10, // UP
		10, // LEFT
		10, // DOWN
		10, // RIGHT
		14,
		14,
		14,
		14
	};

	const int32 size = _board->GetSize();

	// ClosedList
	// close[y][x] -> (y, x)에 방문을 했는지 여부
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	// best[y][x] -> 지금까지 (y,x)에 대한 가장 좋은 비용 (작을 수록 좋음)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// 부모 추적 용도
	map<Pos, Pos> parent;

	// OpenList
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 1) 예약(발견) 시스템 구현
	// - 이미 더 좋은 경로를 찾았다면 스킵
	// 2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수
	// - openList에서 찾아서 제거한다거나.
	// - pq에서 pop한 다음에 무시한다거나. 

	// 초기값
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로로 찾아서
		// 더 빠른 경로로 인해서 이미 방문(closed)된 경우 스킵
		// [둘 중 선택]
		if (closed[node.pos.y][node.pos.x])
			continue;
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 방문
		closed[node.pos.y][node.pos.x] = true;

		// 목적지에 도착했으면 바로 종료
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			// 갈 수 있는 지역은 맞는지 확인
			if (CanMove(nextPos) == false)
				continue;
			// [선택] 이미 방문한 곳이면 스킵
			if (closed[nextPos.y][nextPos.x])
				continue;

			// 비용 계산
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			// 다른 경로에서 더 빠른 길은 찾았으면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// 예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}

	// 거꾸로 거슬러 올라간다
	Pos pos = dest;

	absLocs.clear();
	index = 0;

	while (true)
	{
		absLocs.push_back(pos);

		// ½ÃÀÛÁ¡Àº ÀÚ½ÅÀÌ °ð ºÎ¸ðÀÌ´Ù
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(absLocs.begin(), absLocs.end());
}
