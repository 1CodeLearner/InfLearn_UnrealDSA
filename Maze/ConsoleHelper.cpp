#include "ConsoleHelper.h"
#include "pch.h"
#include "ConsoleHelper.h"

void ConsoleHelper::setCursorPosition(int32 x, int32 y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y)};
	::SetConsoleCursorPosition(output, pos);
}

void ConsoleHelper::SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<int16>(color));
}

void ConsoleHelper::ShowConsoleCursor(bool Flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo; 
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = Flag; 
	::SetConsoleCursorInfo(output, &cursorInfo);

}
