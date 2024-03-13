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
}

void Player::Update(uint64 deltaTime)
{
	
}
