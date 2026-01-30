#pragma once

#include "Common/Common.h"
#include <Windows.h>

namespace Wanted 
{
	//콘솔에 텍스트 색상 등을 저장할 때 사용할 색상 열거형
	enum class WANTED_API Color : unsigned short
	{
		Black = 0,
		Blue = FOREGROUND_BLUE,
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		White = Blue | Green | Red, // + 해도 | 와 같음
	};
}