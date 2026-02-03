#include "ScreenBuffer.h"
#include <iostream>
#include "Renderer.h"

namespace Wanted
{
	ScreenBuffer::ScreenBuffer(const Vector2& screenSize)
		:screenSize(screenSize)
	{
		//Console Output 생성
		buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);


		//예외 처리
		if (buffer == INVALID_HANDLE_VALUE)
		{
			MessageBoxA(nullptr,"ScreenBuffer - Failed to  create buffer", "Buffer creation rror",MB_OK);

			__debugbreak;
		}

		//버퍼 생성 후에는 크기 지정
		SMALL_RECT rect;
		rect.Left = 0;
		rect.Top = 0;
		rect.Right = static_cast<short>(screenSize.x - 1);
		rect.Bottom = static_cast<short>(screenSize.y - 1);

		if (SetConsoleWindowInfo(buffer, true, &rect))
		{
			//DWORD errorCode = GetLastError();
			std::cerr << "Failed to set console window info\n";
			__debugbreak;


		}

		//버퍼 크기 설정
		if (!SetConsoleScreenBufferSize(buffer, screenSize))
		{
			std::cerr << "Failed to set console buffer info\n";
			__debugbreak;
		}

		//커서끄기
		CONSOLE_CURSOR_INFO info;
		GetConsoleCursorInfo(buffer, &info);

		// 끄도록 설정.
		info.bVisible = false;
		SetConsoleCursorInfo(buffer, &info);

	}
	ScreenBuffer::~ScreenBuffer()
	{
		if (buffer)
		{
			CloseHandle(buffer);
		}
	}


	void ScreenBuffer::Clear()
	{
		//실제로 화명을 지우고 난 뒤에 몇 글자를 썻는지 반환 받는데 사용
		DWORD writetenCount = 0;

		//콘솔 버퍼에 있는 화면 지우기
		//그래픽스 -> 지우기 -> 한 색상(또는 값)으로 덮어쓰기 //지우기는 없다
		FillConsoleOutputCharacterA(buffer, ' ', screenSize.x * screenSize.y, Vector2::Zero, &writetenCount);
	}

	void ScreenBuffer::Draw(CHAR_INFO* charInfo)
	{

		//설정할 버퍼의 크키
		SMALL_RECT writeRegion = {};
		writeRegion.Left = 0;
		writeRegion.Top = 0;
		writeRegion.Right = static_cast<short>(screenSize.x-1);
		writeRegion.Bottom = static_cast<short>(screenSize.y - 1);

		//버퍼에 전달 받은 글자 배열 설정
		WriteConsoleOutputA(buffer, charInfo, screenSize, Vector2::Zero, &writeRegion);
	}
}