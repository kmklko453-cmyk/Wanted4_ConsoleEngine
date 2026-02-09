#pragma once

#include "Actor/Actor.h"
#include "actor/TeamMate.h"
#include "Math/Vector2f.h"

using namespace Wanted;

class Ball : public Actor
{
	// RTTI 등록.
	RTTI_DECLARATIONS(Ball, Actor)

public:
	Ball(const Vector2& Position);
	~Ball();
	
	virtual void Tick(float deltaTime) override;


	inline Vector2f ToVector2f(const Vector2& v)
	{
		return Vector2f(static_cast<float>(v.x), static_cast<float>(v.y));
	}
	
	inline Vector2 ToVector2(const Vector2f& v)
	{
		return Vector2(static_cast<int>(v.x), static_cast<int>(v.y));
	}
	void setTp(const Vector2& start, const Vector2& v) { SetPosition(start); targetPos = v; inFlight = true; }

	inline bool IsInFlight() const {return inFlight;}



private:
	//공 날라 가는 속도
	float moveSpeed = 5.0f;

	//팀 동료 위치
	Vector2 targetPos ;

	//골대 위치
	Vector2 posT1;
	Vector2 posT2;

	bool inFlight = false;


	


};
