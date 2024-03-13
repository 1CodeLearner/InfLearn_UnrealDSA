#pragma once

class Board;

class Player
{
public:
	void Init(Board* board);
	void Update(uint64 deltaTime);

	Pos GetPosition() const {return _pos;}
	void SetPosition(Pos pos) {_pos = pos;}

private:
	Board* _board = nullptr;
	int32 _dir = DIR_UP;
	Pos _pos = {};
};

