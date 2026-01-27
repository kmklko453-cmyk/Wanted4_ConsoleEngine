#pragma once

#include "Common/Common.h"

namespace Wanted
{

	//전방 선언
	class Input;

	//Main game engine class
	class WANTED_API Engine // 동작 행동
	{
	public:
		Engine();
		~Engine();

		//엔진 루프(게임루프)
		void Run();

		//엔진 종료 함수
		void QuitEngine();

		// 새 레벨을 추가(설정 )하는 함수
		void SetNewLevel(class Level* newLevel);

	private:

		//게임 플레이 시작 함수
		//unity 같은 경우 Start/Awake
		void BeginPlay();

		//업데이트 함수
		void Tick(float deltaTime);

		//그리기 함수 (Draw/Render)
		void Draw();

	private:
		//엔진 종료 플래그
		bool isQuit = false;

		//입력 관리자
		Input* input = nullptr;

		//메인 레벨
		class Level* mainLevel = nullptr;


	};

}



