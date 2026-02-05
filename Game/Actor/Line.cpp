#include "Line.h"

Line::Line(const Vector2& position)
	:super("@", position, Color::White)
{
	sortingOrder = 0;
}
