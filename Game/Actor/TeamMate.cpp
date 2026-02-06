#include "TeamMate.h"

TeamMate::TeamMate(const char* image, const Vector2& position, Color color, CheckTeamMate number)
	:super(image,position,color)
{
	sortingOrder = 10;

}

