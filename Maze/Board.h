#pragma once
#include "ConsoleHelper.h"

class Player;

enum
{
	BOARD_MAX_SIZE = 100
};

enum class TileType 
{
	NONE = 0, 
	EMPTY,
	WALL
};

class Board
{
public:
	Board();
	~Board();

	void Init(int32 size, Player* player);
	void Render();

	void GenerateMap();

	Pos GetStartPos() const { return Pos{1 , 1}; }
	Pos GetEndPos() const {return Pos{_size - 2, _size - 2}; }

private:
	TileType _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	int32 _size = 0;

	TileType GetTileType(Pos pos);
	ConsoleColor GetTileColor(Pos pos);

	Player* _player;
};

