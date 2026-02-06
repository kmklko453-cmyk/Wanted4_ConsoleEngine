#include "Ball.h"
#include "Target.h"
#include "Player.h"
#include "Level/Level.h"



#include <vector>


Ball::Ball(const Vector2& Position)
	: super("B", Position, Color::Blue)
{
	// 그리기 우선순위 설정.
	sortingOrder = 5;
}

Ball::~Ball()
{
}

void Ball::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	Level* level = GetOwner();
	if (!level) return;

	std::vector<Target*> targets;
	std::vector<Player*> player;
	level->GetActorInstance<Target>(targets);



	if (!targets.empty())
	{
		posT1 = targets[0]->GetPosition();
		posT2 = targets[1]->GetPosition();
		// pos 사용
	}

	if (targets.empty()) return;

	Vector2 ballPos = GetPosition();

	Vector2f posT1f = ToVector2f(posT1);
	Vector2f posBf = ToVector2f(ballPos);


	Vector2f dir;
	dir.x = posT1f.x - posBf.x;
	dir.y = posT1f.y - posBf.y;

	float len = sqrt(dir.x * dir.x + dir.y * dir.y);

	float nx = dir.x / len;
	float ny = dir.y / len;


	posBf.x += (nx * 10) * moveSpeed * deltaTime;
	posBf.y += (ny * 10) * moveSpeed * deltaTime;

	SetPosition(ToVector2(posBf));


}