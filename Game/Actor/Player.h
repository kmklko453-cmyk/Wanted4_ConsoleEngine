#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(const Vector2& position);
	Player(const char* image , const Vector2& position , Color color );

private:

	// 슛 함수.
	void Shoot();

	// 발사 가능여부 확인 함수.
	bool CanShoot() const;

	//팀 동료 패스 키


	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};
