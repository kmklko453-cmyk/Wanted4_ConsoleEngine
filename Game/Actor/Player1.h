#pragma once
#include "PlayerBase.h"

using namespace Wanted;

class Player1 : public PlayerBase
{
	RTTI_DECLARATIONS(Player1,PlayerBase)

public:
	Player1(const Vector2& position);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

};

