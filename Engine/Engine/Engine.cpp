#include "Engine.h"
#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Engine::Engine()
	{
	}

	Engine::~Engine() 
	{
	}

	void Engine::Run()
	{
		//시계의 정밀도 // 정밀도로 나누면 됨 QueryPerformanceCounter는 1000만 1/1000만
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		//프레임 계산용 변수
		//__int64
		int64_t currentTime = 0;
		int64_t previousTime = 0;
	
		//하드웨어 타이머로 시간 구하기
		LARGE_INTEGER time; 
		QueryPerformanceCounter(&time);
		
		//엔진 시작 직전에는 두 시간 값을 같게 맞춤
		currentTime = time.QuadPart;
		previousTime = currentTime; //전프레임 타임에 시간을 안넣으면 값이 커짐.

		//기준 프레임( 단위: 초)
		float targetFrameRate = 120.0f; // 1초에 240 프레임 
		float oneFrameTime = 1.0f / targetFrameRate; // 1/240초


		// 엔진 루프(게임 루프)
		//! -> Not -> bool값 뒤집기 
		while (!isQuit)
		{
			//timeGetTime(); 밀리초 단위 검색 1/1000 = 0.001초 
			
			//현재 시간 구하기
			QueryPerformanceCounter(&time);  
			currentTime = time.QuadPart;


			// 프레임 시간 계산
			float deltaTime 
				= static_cast<float>(currentTime - previousTime);

			//초단위 변환
			deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

			//고정 프레임 기법
			if (deltaTime >= oneFrameTime)
			{
				ProcessInput();

				//프레임 처리
				Tick(deltaTime);
				Draw();

				//이전 시간 값 갱신
				previousTime = currentTime;
			}

		}

		// Todo : 정리 작업 


	}
	void Engine::QuitEngine()
	{
		isQuit = true;
	}
	void Engine::ProcessInput()
	{
	}
	void Engine::Tick(float deltaTime)
	{
		std::cout
			<< "DeltaTime: " << deltaTime
			<< ", FPS: " << (1.0f / deltaTime) << "\n";
	}
	void Engine::Draw()
	{
	}
}