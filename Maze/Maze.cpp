
#include <iostream>
#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

int main()
{
	Board board;
	Player player;

	board.Init(25, &player);
	player.Init(&board);
	
	uint64 lastTick = 0;
	
	::srand(static_cast<unsigned>(time(nullptr)));

	while (true)
	{
#pragma region frame manager
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick;
		/*
		// if you want to set hard limit on number of frame rate
		* if(delta < certainValueLimit )
			continue;
		*/
		lastTick = currentTick;
#pragma endregion

		//입력
		//로직
		//렌더링

		board.Render();
	}
}
