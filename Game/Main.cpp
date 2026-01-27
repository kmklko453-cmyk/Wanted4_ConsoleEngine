#include <iostream>
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/TestLevel.h"
#include "Actor/TestActor.h"
#include "Actor/Actor.h"

int main()
{
	Wanted::Engine engine;
	engine.SetNewLevel(new TestLevel());
	engine.Run();

}