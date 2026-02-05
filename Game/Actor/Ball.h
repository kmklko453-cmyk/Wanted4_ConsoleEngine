#pragma once

#include "Actor/Actor.h"
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
	
	Vector2f SetDir(Vector2f& goal, Vector2f& pos);

	inline Vector2f ToVector2f(const Vector2& v)
	{
		return Vector2f(static_cast<float>(v.x), static_cast<float>(v.y));
	}
	
	inline Vector2 ToVector2(const Vector2f& v)
	{
		return Vector2(static_cast<int>(v.x), static_cast<int>(v.y));
	}

private:
	//공 날라 가는 속도
	float moveSpeed = 5.0f;

	float yPosition = 0.0f;
	float xPosition = 0.0f;

};
