#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init(int32 size, Player* player)
{
	_size = size;
	_player = player;
	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::setCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);
	ConsoleHelper::SetCursorColor(ConsoleColor::RED);

	const char* TILE = "■";

	for (int32 y = 0; y < 25; ++y)
	{
		for (int32 x = 0; x < 25; ++x)
		{
			ConsoleColor color = GetTileColor(Pos{ y,x });
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}
		cout << '\n';
	}
}


//Binary Tree 미로 생성 알고리즘
// - Mazes For Programmers
void Board::GenerateMap()
{
	for (int32 y = 0; y < _size; ++y)
	{
		//Create empty space for all tiles whose x and y are both odd numbers 
		for (int32 x = 0; x < _size; ++x)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_tile[y][x] = TileType::WALL;
			}
			else // x and y are both odd values
			{
				_tile[y][x] = TileType::EMPTY;
			}
		}
	}
	//랜덤으로 우측 혹은 아래로 길을 뚫는 작업
	for (int32 y = 0; y < _size; ++y)
	{
		for (int32 x = 0; x < _size; ++x)
		{
			//if tile is Wall
			//if the tile is the outer-most edge of board
			if (x % 2 == 0 || y % 2 == 0)
			{
				continue;
			}
			//if tile is second tile from bottom right corner 
			if (y == _size - 2 && x == _size - 2)
				continue;

			//if tile's x is previous to the left-most edge
			if (x == _size - 2)
			{
				_tile[y + 1][x] = TileType::EMPTY;
				continue;
			}

			//if tile's y is previous to the bottom-most edge
			if (y == _size - 2)
			{
				_tile[y][x + 1] = TileType::EMPTY;
				continue;
			}

			//for tile that contains both odd value x or y
			//Creating randomized path from empty Tiles
			const int32 randValue = ::rand() % 2;
			if (randValue == 0)
			{
				_tile[y][x + 1] = TileType::EMPTY;
			}
			else
			{
				_tile[y + 1][x] = TileType::EMPTY;
			}
		}
	}
}

TileType Board::GetTileType(Pos pos)
{
	if (pos.x < 0 || pos.x >= _size || pos.y < 0 || pos.y >= _size)
	{
		return TileType::NONE;
	}
	return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{

	if (_player->GetPosition() == pos) 
	{
		return ConsoleColor::BLUE;
	}

	if (GetEndPos() == pos) 
	{
		return ConsoleColor::BLACK;
	}
	
	TileType tileType = GetTileType(pos);

	switch (tileType)
	{
	case TileType::EMPTY:
	{
		return ConsoleColor::WHITE;
	}
	case TileType::WALL: {
		return ConsoleColor::GREEN;
	}
	}

	return ConsoleColor::WHITE;
}
