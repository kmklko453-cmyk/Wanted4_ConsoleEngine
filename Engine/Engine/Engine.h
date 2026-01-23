#pragma once

namespace Wanted
{

	//Main game engine class
	class Engine // 동작 행동
	{
		// 데이터 함수도 데이터로 쓸거임.
		struct KeyState
		{
			// 현재 키가 눌렸는지
			bool isKeyDown = false;

			//이전 키가 눌렸는지
			bool wasKeyDown = false;
		};

	public:
		Engine();
		~Engine();

		//엔진 루프(게임루프)
		void Run();

		//엔진 종료 함수
		void QuitEngine();

		//입력 확인 함수
		//이전에 입력이 안됐는데, 현재 입력이 됐으면 1번 호출
		bool GetKeyDown(int keyCode);
		//이전에 입력이 됐는데, 현재 입력이 취소됐으면   1번 호출
		bool GetKeyup(int keyCode);
		// 현재 놀렸으면 반복 호출
		bool GetKey(int keyCode);

	private:
		//입력 처리 함수
		void ProcessInput();

		//업데이트 함수
		void Tick(float deltaTime);

		//그리기 함수 (Draw/Render)
		void Draw();

	private:
		//엔진 종료 플래그
		bool isQuit = false;

		//키 상태 저장용 배열
		KeyState keyStates[255] = {};

	};

}



