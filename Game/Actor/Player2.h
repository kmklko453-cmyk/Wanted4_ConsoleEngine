#pragma once
#include "PlayerBase.h"

using namespace Wanted;

class Player2 : public PlayerBase
{
	RTTI_DECLARATIONS(Player2, PlayerBase)

public:
	Player2(const Vector2& position);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

};

