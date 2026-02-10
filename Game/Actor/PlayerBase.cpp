#include "PlayerBase.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Ball.h"
#include "Target.h"
#include "Level/Level.h"
#include "Game/Game.h"
#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>

using namespace Wanted;

PlayerBase::PlayerBase(const char* image, const Vector2& position, Color color)
	: super(image , position, color)	
{
	
	
}

void PlayerBase::BeginPlay()
{
	

	//std::cout << "TestActor::BeginPlay().\n";
}

void PlayerBase::Tick(float deltaTime)
{
}


void PlayerBase::Shoot(int index)
{
	Level* level = GetOwner();
	if (!level) return;

	std::vector<Ball*> ball;
	std::vector<Target*> target;

	level->GetActorInstance<Target>(target);
	level->GetActorInstance<Ball>(ball);


	if (target.empty() || ball.empty()) return;
	if (ball[0]->IsInFlight()) return;
	if (!ball[0]->IsOwnedBy(this)) return;
	

	Vector2 pP = GetPosition();
	Vector2 tgP = target[index]->GetPosition();

	ball[0]->setTp(pP, tgP);
}

bool PlayerBase::CanShoot() const
{
	return false;
}

void PlayerBase::TryPassToMate(int index)
{
	Level* level = GetOwner();
	if (!level) return;

	std::vector<Ball*> ball;
	std::vector<TeamMate*> tM;

	level->GetActorInstance<TeamMate>(tM);
	level->GetActorInstance<Ball>(ball);


	if (tM.empty() || ball.empty()) return;
	if (ball[0]->IsInFlight()) return;
	if (!ball[0]->IsOwnedBy(this)) return;

	Vector2 bP = GetPosition();
	Vector2 tMP = tM[index]->GetPosition();

	ball[0]->setTp(bP, tMP);
}


void PlayerBase::Draw()
{
	
}

