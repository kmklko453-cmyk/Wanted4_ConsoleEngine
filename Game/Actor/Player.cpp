#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Ball.h"
#include "Level/Level.h"

#include "Game/Game.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>

using namespace Wanted;

Player::Player(const Vector2& position)
	: super("P", position, Color::Red)	
{
	int xPotsition = 27;
	int yPositionn = 17;

	SetPosition(Vector2(xPotsition, yPositionn));

	// 그리기 우선순위 높게 설정.
	sortingOrder = 10;
}

Player::Player(const char* image, const Vector2& position, Color color)
	:super(image,position,color)
{
	sortingOrder = 10;
}

void Player::BeginPlay()
{
	// 상위 함수 호출.
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay();

	//std::cout << "TestActor::BeginPlay().\n";
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// ESC키 처리.
   	if (Wanted::Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 메뉴 활성화.
		Game::Get().ToggleMenu();
		return;
	}

	// Q키 종료.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// Todo: 게임 엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}

	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		Shoot();
	}

	if (Input::Get().GetKeyDown('1'))
	{	
		Level* level = GetOwner();
		if (!level) return;

		std::vector<TeamMate*> tM;

		level->GetActorInstance<TeamMate>(tM);
		
		if (tM.empty())
		{
			return;
		}


		Vector2 tMP = tM[0]->GetPosition();

		
		GetOwner()->AddNewActor(new Ball(position,tMP));
	}
	if (Input::Get().GetKeyDown('2'))
	{
		Level* level = GetOwner();
		if (!level) return;

		std::vector<TeamMate*> tM;

		level->GetActorInstance<TeamMate>(tM);

		if (tM.empty())
		{
			return;
		}


		Vector2 tMP = tM[1]->GetPosition();


		GetOwner()->AddNewActor(new Ball(position, tMP));
	}if (Input::Get().GetKeyDown('3'))
	{
		Level* level = GetOwner();
		if (!level) return;

		std::vector<TeamMate*> tM;

		level->GetActorInstance<TeamMate>(tM);

		if (tM.empty())
		{
			return;
		}


		Vector2 tMP = tM[2]->GetPosition();


		GetOwner()->AddNewActor(new Ball(position, tMP));
	}if (Input::Get().GetKeyDown('4'))
	{
		Level* level = GetOwner();
		if (!level) return;

		std::vector<TeamMate*> tM;

		level->GetActorInstance<TeamMate>(tM);

		if (tM.empty())
		{
			return;
		}


		Vector2 tMP = tM[3]->GetPosition();


		GetOwner()->AddNewActor(new Ball(position, tMP));
	}

	//// 인터페이스 확인.
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	//// 오너십 확인 (null 확인).
	if (!canPlayerMoveInterface && GetOwner())
	{
		// 인터페이스로 형변환.
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}

	// 이동. Todo: 삭제 예정 이동 무브 따로 생성
	if (Input::Get().GetKey(VK_RIGHT) && GetPosition().x < 400)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKey(VK_DOWN) && GetPosition().y < 400)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x, GetPosition().y + 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKey(VK_UP) && GetPosition().y > 0)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x, GetPosition().y - 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}
}


void Player::Shoot()
{
	// 경과 시간 초기화.
		//elapsedTime = 0.0f;

	// 위치 설정.
	

	// 액터 생성.
	GetOwner()->AddNewActor(new Ball(position));
}

bool Player::CanShoot() const
{
	return false;
}

void Player::Draw()
{
	Actor::Draw();
}

