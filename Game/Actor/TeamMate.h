#pragma once
#include "Actor/Actor.h"
#include "Level/Level.h"
#include "Math/Vector2F.h"

using namespace Wanted;

class TeamMate : public Actor
{
	RTTI_DECLARATIONS(TeamMate, Actor)

public:
	TeamMate(const char* image, const Vector2& position , Color color, Vector2 aPositon);

	inline Vector2f ToVector2f(const Vector2& v)
	{
		return Vector2f(static_cast<float>(v.x), static_cast<float>(v.y));
	}

	inline Vector2 ToVector2(const Vector2f& v)
	{
		return Vector2(static_cast<int>(v.x), static_cast<int>(v.y));
	}

	void setTp(const Vector2& start, const Vector2& v) { SetPosition(start); targetPos = v; }

	Vector2 GetH() const { return homePos; }
	Vector2 GetA() const { return AttackPos;}

private:

	virtual void Tick(float deltaTime) override;

	Vector2 targetPos;

	float moveSpeed = 5.0f;

	Vector2 homePos;
	Vector2 AttackPos;



};


