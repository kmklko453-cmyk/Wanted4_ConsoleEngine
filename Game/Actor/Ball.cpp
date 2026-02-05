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

    Vector2 positionT1;
    Vector2 positionT2;
    Vector2 positionP1;
    Vector2 positionP2;

    std::vector<Target*> targets;
    std::vector<Player*> player;
    level->GetActorInstance<Target>(targets);
    level->GetActorInstance<Player>(player);

    if (!targets.empty())
    {
        positionT1 = targets[0]->GetPosition();
        positionT2 = targets[1]->GetPosition();
        // pos 사용
    }

    if (targets.empty()) return;

    Vector2 targetPos = targets[0]->GetPosition();
    Vector2 ballPos = GetPosition();

    Vector2f posT1 = ToVector2f(targetPos);
    Vector2f posB = ToVector2f(ballPos);

    Vector2f dir;
    dir.x = posT1.x - posB.x;
    dir.y = posT1.y - posB.y;

    float len = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 0.0001f)
    {
        float nx = dir.x / len;
        float ny = dir.y / len;

        posB.x += nx * moveSpeed * deltaTime;
        posB.y += ny * moveSpeed * deltaTime;

        SetPosition(ToVector2(posB));
    }

    /*Vector2 dir = SetDir(positionT1, positionP1);

   
    xPosition += dir.x * moveSpeed * deltaTime;
    yPosition += dir.y * moveSpeed * deltaTime;

    Vector2 newPosition = GetPosition();
    newPosition.y = static_cast<int>(yPosition);
    newPosition.x = static_cast<int>(xPosition);
    */

   

}
Vector2f Ball::SetDir(Vector2f& goal, Vector2f& pos)
{
    Vector2f dir = goal - pos;
 ;
 
    return dir;
}
