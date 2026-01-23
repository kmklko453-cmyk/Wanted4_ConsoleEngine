#pragma once

namespace Wanted
{

	//Main game engine class
	class Engine
	{
	public:
	Engine();
	~Engine();

	//엔진 루프(게임루프)
	void Run();

	//엔진 종료 함수
	void QuitEngine();

	private:
		//입력 처리 함수
		void ProcessInput();

		//업데이트 함수
		void Tick(float deltaTime);

		//그리기 함수 (Draw/Render)
		void Draw();

	private:
	bool isQuit = false;
	};

	

}

