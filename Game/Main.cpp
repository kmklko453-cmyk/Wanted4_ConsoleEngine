#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/SokobanLevel.h"

using namespace Wanted;


int main()
{
	//예시 배열
	const int width = 3;
	const int hight = 3;
	CHAR_INFO charArray[3 * 3] = {};


	charArray[2 * width + 1].Char.AsciiChar = 'p';
	charArray[2 * width + 1].Attributes = FOREGROUND_GREEN;

	charArray[0 * width + 1].Char.AsciiChar = '#';
	charArray[0 * width + 1].Attributes = FOREGROUND_RED;

	COORD position = {};
	COORD screenSize;
	screenSize.X = 3;
	screenSize.Y = 3;

	SMALL_RECT writeRegion{ 0,0,static_cast<short>(width),static_cast<short>(hight) };

	WriteConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), charArray, screenSize, position,&writeRegion);


	//CreateConsoleScreenBuffer()
	//SetConsoleActiveScreenBuffer()

	//Wanted::Engine engine;
	//engine.SetNewLevel(new SokobanLevel());
	//engine.Run();

	//Game game;
	//game.Run();

	// 문자 배열을 한번에 콘솔로 넘겨서 그릴 때 사용하는 함수
	/*WriteConsoleOutputA(
	
	);*/

	std::cin.get();

}