#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class Target : public Actor
{
	RTTI_DECLARATIONS(Target, Actor)


public:
	Target(const char* image, const Vector2& position, Color color);
};
