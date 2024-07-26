#pragma once

class Board;

class Player
{
public:
	void Init(Board* board);
	void Update(uint64 deltaTime);

	Pos GetPosition() const {return _loc;}
	void SetPosition(Pos pos) {_loc = pos;}

private:
	Board* _board = nullptr;
	int32 _dir = DIR_UP;
	Pos _loc = {};
	std::vector<Pos> absLocs;
	uint64 totalTime = 0;
	uint64 maxTime = 200;
	int32 index = 0;

	bool CanMove(Pos newPos) const;
	bool AtDestination() const;

	void RightHandRule();
	void BFS();
	void AStar();
	void AStarExample();
	void AnotherAStarPractice();
	void MoreAStar();
};

