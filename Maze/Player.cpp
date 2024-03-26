#include "pch.h"
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

	Pos tempPos = _loc;
	Pos dest = board->GetEndPos();

	Pos dir[4]
	{
		Pos{-1,0}, //up
		Pos{0,-1},	//left
		Pos{1,0},	//down
		Pos{0,1}	//right
	};

	//Right-hand rule
	//우수법
	while (tempPos != dest)
	{
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		//1.현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		if (CanMove(tempPos + dir[newDir]))
		{
			//오른쪽 방향으로 90도 회전
			_dir = newDir;
			//앞으로 한 보 전진
			tempPos += dir[newDir];
			absLocs.push_back(tempPos);
		}
		else if (CanMove(tempPos + dir[_dir]))
		{
			//앞으로 한 보 전진
			tempPos += dir[_dir];
			absLocs.push_back(tempPos);
		}
		else
		{
			//왼쪽 방향으로 90도 회전.
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
