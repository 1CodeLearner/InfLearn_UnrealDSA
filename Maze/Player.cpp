#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_board = board;
	if (_board)
	{
		_pos = _board->GetStartPos();
	}

	Pos tempPos = _pos;
	Pos dest = board->GetEndPos();

	Pos Move[4]
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
		if (CanMove(tempPos + Move[newDir]))
		{
			//오른쪽 방향으로 90도 회전
			_dir = newDir;
			//앞으로 한 보 전진
			tempPos += Move[newDir];
			moves.push_back(Move[newDir]);
		}
		else if (CanMove(tempPos + Move[_dir]))
		{
			//앞으로 한 보 전진
			tempPos += Move[_dir];
			moves.push_back(Move[_dir]);
		}
		else
		{
			//왼쪽 방향으로 90도 회전.
			_dir = (_dir + 1) % DIR_COUNT;
			/*
			switch (_dir)
			{
			case DIR_UP:
				_dir = DIR_LEFT;
				break;
			case DIR_LEFT:
				_dir = DIR_DOWN;
				break;
			case DIR_DOWN:
				_dir = DIR_RIGHT;
				break;
			case DIR_RIGHT:
				_dir = DIR_UP;
				break;
			}
			*/
		}
	}
}

void Player::Update(uint64 deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= maxTime && !AtDestination()) 
	{
		_pos += moves[index];
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
	Pos wat = _pos; 
	return  wat == _board->GetEndPos();
}
