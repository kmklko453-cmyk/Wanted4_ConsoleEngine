#include "Ball.h"
#include "Target.h"
#include "PlayerBase.h"
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
	
	super::Tick(deltaTime);

	Level* level = GetOwner();
	if (!level) return;

	if (!ownerActor)
	{	

		std::vector<PlayerBase*> players;
		level->GetActorInstance<PlayerBase>(players);
		if (players.empty()) return;

		SetOwnActor(players[0]);
		SetLastPlayer(players[0]);

	}

	if (!inFlight && ownerActor)
	{
		
		SetPosition(ownerActor->GetPosition());
		//ResolveContactOwnership();
		
	}


	//비행상태 판단
	if (!(targetPos.x == 0 && targetPos.y == 0))
	{
		Vector2 ballPos = GetPosition();

		Vector2f posT1f = ToVector2f(targetPos);
		Vector2f posBf = ToVector2f(ballPos);


		Vector2f dir;
		dir.x = posT1f.x - posBf.x;
		dir.y = posT1f.y - posBf.y;

		float len = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len < 0.001f)
		{
			inFlight = false;
			//ResolveContactOwnership();
			return;
		}

		float nx = dir.x / len;
		float ny = dir.y / len;


		posBf.x += (nx*5) * moveSpeed * deltaTime;
		posBf.y += (ny*5) * moveSpeed * deltaTime;

		SetPosition(ToVector2(posBf));
		return;
	}
}

void Ball::ResolveContactOwnership()
{

	Level* level = GetOwner();
	if (!level) return;

	std::vector<PlayerBase*> players;
	std::vector<TeamMate*> mates;
	level->GetActorInstance<TeamMate>(mates);
	level->GetActorInstance<PlayerBase>(players);

	
	for (PlayerBase* player : players)
	{
		if (!player || player == ownerActor) continue;
		
		if (TestIntersect(player))
		{
			SetOwnActor(player);
			SetLastPlayer(player);
			targetPos = Vector2::Zero;
		
			return;
		}
	}

	for (TeamMate* mate : mates)
	{
		if (!mate || mate == ownerActor) continue;
		PlayerBase* teamPlayer = nullptr;
		for (PlayerBase* player : players)
		{
			if (player && player->GetColor() == mate->GetColor())
			{
				teamPlayer = player;
				break;
			}
		}
		if (teamPlayer)
		{
			SetOwnActor(teamPlayer);
			// lastPlayer는 패스/슛 시점에 유지(스왑 로직용)

			inFlight = false;
			targetPos = Vector2::Zero;
	
			return;
		}
	}
	
}
