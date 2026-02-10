#include "Player2.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

using namespace Wanted;

Player2::Player2(const Vector2& position)
	:PlayerBase("P", position, Color::Green)
{
	int xPotsition = 60;
	int yPositionn = 17;

	SetPosition(Vector2(xPotsition, yPositionn));

	// 그리기 우선순위 높게 설정.
	sortingOrder = 10;
}


void Player2::BeginPlay()
{
	// 상위 함수 호출.
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay();
}

void Player2::Tick(float deltaTime)
{

	super::Tick(deltaTime);

	// Q키 종료.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// Todo: 게임 엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}

	if (Input::Get().GetKeyDown(VK_DELETE))
	{
		PlayerBase::Shoot(0);
	}

	if (Input::Get().GetKeyDown('7'))
	{
		PlayerBase::TryPassToMate(2);
	}
	if (Input::Get().GetKeyDown('8'))
	{
		PlayerBase::TryPassToMate(3);
	}
	if (Input::Get().GetKeyDown('9'))
	{
		PlayerBase::TryPassToMate(6);
	}

	if (Input::Get().GetKeyDown('0'))
	{
		PlayerBase::TryPassToMate(7);
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

void Player2::Draw()
{
	Actor::Draw();
}

