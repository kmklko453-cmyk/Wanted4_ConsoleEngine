#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class PlayerBase : public Actor
{
	

	RTTI_DECLARATIONS(PlayerBase, Actor)

public:
	PlayerBase(const char* image, const Vector2& position, Color color);

protected:

	// 슛 함수.
	virtual void Shoot(int index);

	// 발사 가능여부 확인 함수.
	bool CanShoot() const;

	// 동료한테 패스 하는 함수
	virtual void TryPassToMate(int index);

	//수비시 포지션 교체 함수
	virtual void  ChangeDefensePosition(int index);

	


	



	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};
