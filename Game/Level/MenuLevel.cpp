#include "MenuLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"
#include <iostream>

MenuLevel::MenuLevel()
{
	//FileRead("MainLevel.txt");
	 //메뉴 아이템 생성.
	items.emplace_back(new MenuItem(
		"Game Start",
		[]()
		{
			// 메뉴 토글 함수 호출.
			Game::Get().ToggleMenu();
		}
	));

	items.emplace_back(new MenuItem(
		"Quit Game",
		[]()
		{
			// 게임 종료.
			Game::Get().QuitEngine();
		}
	));
}

MenuLevel::~MenuLevel()
{
	//배경 버퍼 해제
	/*for (char* line : backgroundBuffer)
	{
		delete[] line;
	}
	backgroundBuffer.clear();*/

	// 기존 메뉴 아이템 제거
	for (MenuItem*& item : items)
	{
		delete item;
		item = nullptr;
	}
	//배열 초기화
	items.clear();
}

//void MenuLevel::FileRead(const char* filename)
//{
//
//	char path[2048] = {};
//	sprintf_s(path, 2048, "../Assets/%s", filename);
//	// 파일 열기
//	FILE* file = nullptr;
//
//
//	// 예외 처리
//	if (!file)
//	{
//		std::cerr << "Failed to open map file.\n";
//		__debugbreak();
//		return;
//	}
//
//	// 파일 크기 읽기
//	fseek(file, 0, SEEK_END);
//	size_t fileSize = ftell(file);
//	rewind(file);
//
//	// 데이터 읽기
//	char* data = new char[fileSize + 1];
//	size_t readSize = fread(data, sizeof(char), fileSize, file);
//	data[readSize] = '\0';
//
//	// 기존 버퍼 해제
//	for (char* line : backgroundBuffer)
//	{
//		delete[] line;
//	}
//	backgroundBuffer.clear();
//
//	// 줄 개수 계산
//	int lineCount = 1;
//	for (size_t i = 0; i < readSize; ++i)
//	{
//		if (data[i] == '\n') ++lineCount;
//	}
//	backgroundBuffer.reserve(lineCount);
//
//	// 줄 잘라서 저장
//	int start = 0;
//	for (size_t i = 0; i <= readSize; ++i)
//	{
//		if (i == readSize || data[i] == '\n')
//		{
//			int len = (int)i - start;
//			if (len > 0 && data[start + len - 1] == '\r')
//			{
//				--len;
//			}
//
//			char* line = new char[len + 1];
//			memcpy(line, data + start, len);
//			line[len] = '\0';
//			backgroundBuffer.emplace_back(line);
//
//			start = (int)i + 1;
//		}
//	}
//
//	delete[] data;
//	fclose(file);
//}

void MenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	// 입력 처리 (방향키 위/아래키, 엔터키, ESC키).
	// 배열 길이.
	static int length = static_cast<int>(items.size());
	if (Input::Get().GetKeyDown(VK_UP))
	{
		// 인덱스 돌리기 (위 방향으로).
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		// 인덱스 돌리기.
		currentIndex = (currentIndex + 1) % length;
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 메뉴 아이템이 저장한 함수 포인터 호출.
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 메뉴 토글.
		Game::Get().ToggleMenu();

		// 인덱스 초기화.
		currentIndex = 0;
	}
}

void MenuLevel::Draw()
{
	// 배경 먼저 출력
	/*for (int y = 0; y < (int)backgroundBuffer.size(); ++y)
	{
		Renderer::Get().Submit(backgroundBuffer[y], Vector2(0, y));
	}*/

	// 기존 메뉴 타이틀/아이템 출력
	Renderer::Get().Submit("Console Basketball Association ", Vector2(35,13));

	for (int ix = 0; ix < (int)items.size(); ++ix)
	{
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;
		Renderer::Get().Submit(items[ix]->text, Vector2(45, 15 + ix), textColor);
	}

}
