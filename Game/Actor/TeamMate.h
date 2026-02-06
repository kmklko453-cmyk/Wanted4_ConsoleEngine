#pragma once
#include "Actor/Actor.h"
#include "Level/Level.h"
using namespace Wanted;

enum class CheckTeamMate
{
	one,
	two,
	three,
	four
};

class TeamMate : public Actor
{
	RTTI_DECLARATIONS(TeamMate, Actor)

public:
	TeamMate(const char* image, const Vector2& position , Color color, CheckTeamMate number);


private:



};


