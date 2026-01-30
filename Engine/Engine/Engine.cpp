#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"
#include "Util/Util.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	//전역 변수 초기화
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		//전역 변수 초기화
		instance = this;

		//입력 생성 관리자
		input = new Input();

		//설정 파일 로드
		LoadSetting();

		void turnOffCursor();
		
	}

	Engine::~Engine()
	{
		//메인 레벨 제거
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		//입력 관리자 제거
		if (input)
		{
			delete input;
			input = nullptr;
		}
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
		//float targetFrameRate = 120.0f; // 1초에 240 프레임 
		setting.framerate = setting.framerate == 0.0f ? 60.0f : setting.framerate;
		float oneFrameTime = 1.0f / setting.framerate; // 1/240초


		// 엔진 루프(게임 루프)
		//! -> Not -> bool값 뒤집기 
		while (!isQuit)
		{
			//TimeGetTime(); 밀리초 단위 검색 1/1000 = 0.001초 

			//현재 시간 구하기
			QueryPerformanceCounter(&time); //windows함수 h/w 시간 사용 천만분의 1초
			currentTime = time.QuadPart;


			// 프레임 시간 계산, 정밀도로 나눔
			float deltaTime
				= static_cast<float>(currentTime - previousTime);

			//초단위 변환
			deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

			//고정 프레임 기법
			if (deltaTime >= oneFrameTime)
			{
				input->ProcessInput();

				//프레임 처리
				BeginPlay();
				Tick(deltaTime);
				Draw();

				//이전 시간 값 갱신
				previousTime = currentTime;

				input->SavePreviousInputStates();

				// 레벨에 요청된 추가/제거 처리
				if (mainLevel)
				{
					mainLevel->ProcessAddAndDestroyActors();
				}



			}

		}

		// Todo : 정리 작업 
		std::cout << "Engine has been shutdown...\n";

		// 커서 켜기.
		Util::TurnOnCursor();

	}
	void Engine::QuitEngine()
	{
		isQuit = true;
	}

	void Engine::SetNewLevel(Level* newLevel)
	{
		//기존 레벨 있는지 확인
		//있으면 기존 레벨 제거
		//Todo: 임시 코드 레벨 전환할 때는 바로 제거하면 안됨
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		//레벨 설정
		mainLevel = newLevel;

	}
	Engine& Engine::Get()
	{
		//예외 처리
		if (!instance)
		{
			std::cout << " Error: Engine::Get(). instance is null\n";
			__debugbreak;
		}

		return *instance;
	}

	void Engine::LoadSetting()
	{
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt");
		//예외 처리 
		if (!file)
		{
			std::cout << "Failed to open engine setting file. \n";
			__debugbreak;
			return;
		}

		//파일에서 읽은 데이터 담을 버퍼
		char buffer[2048] = {};
		
		// 파일에서 읽기
		size_t readSize = fread(buffer, sizeof(char), 2048, file);

		//문자열 포맷을 활용해서 데이터 추출
		sscanf_s(buffer, "framerate = %f", &setting.framerate);

		//파일 닫기
		fclose(file);
	}

	void Engine::BeginPlay()
	{
			//레벨이 있으면 이벤트 전달
			if (!mainLevel)
			{
				std::cout << "mainLevel is empty.\n";
				return;
			}
			mainLevel->BeginPlay();

	}
	void Engine::Tick(float deltaTime)
	{
		//std::cout
		//	<< "DeltaTime: " << deltaTime
		//	<< ", FPS: " << (1.0f / deltaTime) << "\n";


		//레벨에 이벤트 흘리기
		//예외처리
		if (!mainLevel)
		{
			std::cout << "Error : Engine::Tick(). mainLevel is empty\n";
			return;
		}
		mainLevel->Tick(deltaTime);
	}
	void Engine::Draw()
	{
		if (!mainLevel)
		{
			std::cout << "Error : Engine::Draw(). mainLevel is empty\n";
			return;
		}
		mainLevel->Draw();
	}
}
