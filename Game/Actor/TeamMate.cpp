#include "TeamMate.h"
#include "Math/Vector2F.h"
TeamMate::TeamMate(const char* image, const Vector2& position, Color color, Vector2 aPosition)
	:super(image,position,color), AttackPos(aPosition)
{
	sortingOrder = 10;

}

void TeamMate::Tick(float deltaTime)
{

	super::Tick(deltaTime);


	Vector2 ballPos = GetPosition();

	Vector2f posT1f = ToVector2f(targetPos);
	Vector2f posBf = ToVector2f(ballPos);


	Vector2f dir;
	dir.x = posT1f.x - posBf.x;
	dir.y = posT1f.y - posBf.y;

	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len < 0.001f)
	{
		//inFlight = false;
		//ResolveContactOwnership();
		return;
	}

	float nx = dir.x / len;
	float ny = dir.y / len;


	posBf.x += (nx * 5) * moveSpeed * deltaTime;
	posBf.y += (ny * 5) * moveSpeed * deltaTime;

	SetPosition(ToVector2(posBf));

}

