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
	std::vector<Pos> moves;
	uint64 totalTime = 0;
	uint64 maxTime = 10;
	int32 index = 0;

	bool CanMove(Pos newPos) const;
	bool AtDestination() const;
};

