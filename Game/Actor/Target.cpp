#include "Target.h"

Target::Target(const char* image, const Vector2& position, Color color)
	:super(image, position, color)
{
	// 그리기 우선순위 설정.
	sortingOrder = 3;
}
