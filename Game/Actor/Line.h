#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class Line : public Actor
{
	RTTI_DECLARATIONS(Line,Actor)

public:
	Line(const Vector2& position);

};

