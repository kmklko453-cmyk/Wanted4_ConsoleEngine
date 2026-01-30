#include "Level.h"
#include "Actor/Actor.h"

namespace Wanted
{
	Level::Level()
	{
	}

	Level::~Level()
	{
		//메모리 정리
		for (Actor*& actor : actors)
		{
			//액터 객체 메모리 해제
			if (actor)
			{
				delete actor;
				actor = nullptr;

			}
		}

		//배열 초기화
		actors.clear();

	}

	void Level::BeginPlay()
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : actors)
		{
			// 이미 BeginPlat 호출된 액터는 건너뛰기
			if (actor->HasBeganPlay())
			{
				continue;
			}

			actor->BeginPlay();
		}

	}
	void Level::Tick(float deltaTime)
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}
	void Level::Draw()
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : actors) // 배열 크기가 달라지면 안됨
		{
			actor->Draw();
		}
	}
	void Level::AddNewActor(Actor* newActor)
	{
		// 나중에 프레임 처리 고려해서 따로 추가 작업 해야함
		//actors.push_back(newActor); 아래와 같음 이건 Lvalue 현재 버전에서는 Rvalue도 고려함
		//actors.emplace_back(newActor); // 이건 Rvalue Reference 고려함 
		addRequestedActors.emplace_back(newActor);

	}
	void Level::ProcessAddAndDestroyActors()
	{
		//제거 처리
		for (int ix = 0; ix < static_cast<int>(actors.size()); )
		{
			//제거 요청된 액터가 있는지 확인
			if (actors[ix]->DestroyRequested())
			{
				//삭제 처리
				delete actors[ix];
				actors.erase(actors.begin() + ix); //동적 배열에서 순차 배열 삭제 연산을 
				continue;
			}
			++ix;
		}

		//추가 처리
		if (addRequestedActors.size() == 0)
		{
			return;
		}

		for (Actor* const actor : addRequestedActors ) 
		{
			actors.emplace_back(actor);
		}
		
		//처리가 끝났으면 배열 초기화.
		addRequestedActors.clear();

	}
}