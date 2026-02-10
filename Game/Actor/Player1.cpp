#include "Player1.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

using namespace Wanted;

Player1::Player1(const Vector2& position)
	:PlayerBase("P",position, Color::Red)
{
	int xPotsition = 27;
	int yPositionn = 17;

	SetPosition(Vector2(xPotsition, yPositionn));

	// 그리기 우선순위 높게 설정.
	sortingOrder = 10;
}


void Player1::BeginPlay()
{
	// 상위 함수 호출.
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay();
}

void Player1::Tick(float deltaTime)
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

	if (Input::Get().GetKeyDown('F'))
	{
		Shoot(1);
	}

	if (Input::Get().GetKeyDown('1'))
	{
		TryPassToMate(0);
		ChangeDefensePosition(0);
	}
	if (Input::Get().GetKeyDown('2'))
	{
		TryPassToMate(1);
		ChangeDefensePosition(1);
	}
	if (Input::Get().GetKeyDown('3'))
	{
		TryPassToMate(4);
		ChangeDefensePosition(4);
	}

	if (Input::Get().GetKeyDown('4'))
	{
		TryPassToMate(5);
		ChangeDefensePosition(5);
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
	if (Input::Get().GetKey('D') && GetPosition().x < 400)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKey('A') && GetPosition().x > 0)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKey('S') && GetPosition().y < 400)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x, GetPosition().y + 1);
		if (canPlayerMoveInterface->CanMove(newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKey('W') && GetPosition().y > 0)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x, GetPosition().y - 1);
		if (canPlayerMoveInterface->CanMove(newPosition))
		{
			SetPosition(newPosition);
		}
	}
}

void Player1::Draw()
{
	Actor::Draw();
}

