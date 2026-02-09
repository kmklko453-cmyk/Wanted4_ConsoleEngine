#include "SokobanLevel.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Ball.h"
#include "Actor/Target.h"
#include "Actor/Line.h"
#include "Actor/TeamMate.h"
#include "Render/Renderer.h"
#include "Core/Input.h"
#include "Util/Util.h"

#include <iostream>

/*
#: 벽(Wall)
.: 바닥(Ground)
p: 플레이어(Player)
b: 박스(Box)
t: 타겟(Target)
*/

SokobanLevel::SokobanLevel()
{
	// TestActor 액터를 레벨에 추가.
	//AddNewActor(new Player());
	//LoadMap("Map.txt");
	LoadMap("court.txt");
}

void SokobanLevel::Draw()
{
	super::Draw();

	// 게임 클리어인 경우. 메시지 출력.
	if (isGameClear)
	{
		// 콘솔 위치/색상 설정.
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);

		// 게임 클리어 메시지 출력.
		std::cout << "Game Clear!";
	}
	ShowScore();
}

void SokobanLevel::LoadMap(const char* filename)
{
	// 파일 로드.
	// 최종 파일 경로 만들기. ("../Assets/filename")
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	// 예외 처리.
	if (!file)
	{
		// 표준 오류 콘솔 활용.
		std::cerr << "Failed to open map file.\n";

		// 디버그 모드에서 중단점으로 중단해주는 기능.
		__debugbreak();
	}

	// 맵 읽기.
	// 맵 크기 파악: File Position 포인터를 파일의 끝으로 이동.
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기.
	size_t fileSize = ftell(file);

	// File Position 처음으로 되돌리기.
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1];

	// 데이터 읽기.
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	// 읽어온 문자열을 분석(파싱-Parsing)해서 출력.
	// 인덱스를 사용해 한문자씩 읽기.
	int index = 0;

	// 객체를 생성할 위치 값.
	Wanted::Vector2 position;

	while (true)
	{
		// 종료 조건.
		if (index >= fileSize)
		{
			break;
		}

		// 캐릭터 읽기.
		char mapCharacter = data[index];
		++index;

		// 개행 문자 처리.
		if (mapCharacter == '\n')
		{
			//std::cout << "\n";
			// y좌표는 하나 늘리고, x 좌표 초기화.
			++position.y;
			position.x = 0;
			continue;
		}

		/*
		#: 벽(Wall)
		.: 바닥(Ground)
		p: 플레이어(Player)
		b: 박스(Box)
		t: 타겟(Target)
		*/
		// 한문자씩 처리.
		switch (mapCharacter)
		{
		case '#':
		case '0':
			//std::cout << "#";
			AddNewActor(new Wall(position));
			break;

		case ' ':
			//std::cout << " ";
			AddNewActor(new Ground(position));
			break;

		case '@':
			//std::cout << " ";
			AddNewActor(new Line(position));
			break;

		case 'P':
			//std::cout << "P";
			// 플레이어도 이동 가능함.
			// 플레이어 밑에 땅이 있어야 함.
			AddNewActor(new Player(position));
			AddNewActor(new Ground(position));
			break;

		case '1':
			AddNewActor(new TeamMate("1", position, Color::Red, CheckTeamMate::one));
			AddNewActor(new Ground(position));
			break;

		case '2':
			AddNewActor(new TeamMate("2", position, Color::Red, CheckTeamMate::two));
			AddNewActor(new Ground(position));
			break;

		case '3':
			AddNewActor(new TeamMate("3", position, Color::Red, CheckTeamMate::three));
			AddNewActor(new Ground(position));
			break;

		case '4':
			AddNewActor(new TeamMate("4", position, Color::Red, CheckTeamMate::four));
			AddNewActor(new Ground(position));
			break;

		case 'B':
			//std::cout << "B";
			// 박스는 이동 가능함.
			// 박스가 옮겨졌을 때 그 밑에 땅이 있어야 함.
			AddNewActor(new Ball(position));
			break;

		case 'T':
			//std::cout << "T";
			AddNewActor(new Target("T", position, Color::Red));
			++targetScore;
			break;

		case 't':
			//std::cout << "T";
			AddNewActor(new Target("t", position, Color::Blue));
			++targetScore;
			break;
		}

		// x 좌표 증가 처리.
		++position.x;
	}

	// 사용한 버퍼 해제.
	delete[] data;

	// 파일이 정상적으로 열렸으면 닫기.
	fclose(file);
}

void SokobanLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	ChangePosition();
	CheckGameClear();
}

//Todo: 포지션 변경 구현
void SokobanLevel::ChangePosition()
{
	if (Input::Get().GetKey(VK_SPACE)) return;
	std::vector<Player*> players;
	std::vector<Ball*> balls;
	std::vector<TeamMate*> teamMates;
	GetActorInstance<Ball>(balls);
	GetActorInstance<TeamMate>(teamMates);
	GetActorInstance<Player>(players);
	if (players.empty() || balls.empty() || teamMates.empty())
		return;


	for (Ball* const ball : balls)
	{
		for (TeamMate* const tM : teamMates)
		{
			if (ball->TestIntersect(tM))
			{
				Vector2 temp = players[0]->GetPosition();
				players[0]->SetPosition(tM->GetPosition());
				tM->SetPosition(temp);
				return;
			}
		}
	}
}

bool SokobanLevel::CanMove(
	const Wanted::Vector2& playerPosition,
	const Wanted::Vector2& nextPosition)
{
	// 레벨에 있는 박스 액터 모으기.
	// 박스는 플레이어가 밀기 등 추가적으로 처리해야하기 때문.
	std::vector<Actor*> boxes;

	// 레벨에 배치된 전체 액터를 순회하면서 박스 찾기.
	for (Actor* const actor : actors)
	{
		// 액터가 박스 타입인지 확인.
		if (actor->IsTypeOf<Ball>())
		{
			boxes.emplace_back(actor);
			continue;
		}
	}

	// 이동하려는 위치에 박스가 있는지 확인.
	Actor* boxActor = nullptr;
	for (Actor* const box : boxes)
	{
		// 위치 비교.
		if (box->GetPosition() == nextPosition)
		{
			boxActor = box;
			break;
		}
	}

	// 경우의 수 처리.
	// 이동하려는 곳에 박스가 있는 경우.
	if (boxActor)
	{
		// #1: 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인.
		// 두 위치 사이에서 이동 방향 구하기 (벡터의 뺄셈 활용).
		// 이동 로직에서 두 벡터를 더한다는 것은
		// 둘 중 하나는 위치(Location)이고 다른 하나는 벡터(Vector).
		Vector2 direction = nextPosition - playerPosition;
		Vector2 newPosition = boxActor->GetPosition() + direction;

		// 박스 검색.
		for (Actor* const otherBox : boxes)
		{
			// 앞에서 검색한 박스와 같다면 건너뛰기.
			if (otherBox == boxActor)
			{
				continue;
			}

			// 다른 박스가 있는지 확인.
			if (otherBox->GetPosition() == newPosition)
			{
				// 두 개의 박스가 겹쳐진 방향으로는 이동 못함.
				return false;
			}
		}

		// 검색.
		for (Actor* const actor : actors)
		{
			if (actor->GetPosition() == newPosition)
			{
				// #2: 벽이면 이동 불가.
				if (actor->IsTypeOf<Wall>())
				{
					return false;
				}

				//3: 그라운드 또는 타겟이면 이동 가능.
				if (actor->IsTypeOf<Ground>() || actor->IsTypeOf<Target>() || actor->IsTypeOf<Line>())
				{
					// 박스 이동 처리.
					boxActor->SetPosition(newPosition);

					// 게임 점수 확인.
					//isGameClear = CheckGameClear();

					// 플레이어 이동 가능.
					return true;
				}
			}
		}
	}

	// 이동하려는 곳에 박스가 없는 경우.
	// -> 이동하려는 곳에 있는 액터가 벽이 아니면 이동 가능.
	for (Actor* const actor : actors)
	{
		// 먼저, 이동하려는 위치에 있는 액터 검색.
		if (actor->GetPosition() == nextPosition)
		{
			// 이 액터가 벽인지 확인.
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}

			// 그라운드 또는 타겟.
			return true;
		}
	}

	// 에러.
	return false;
} //canmove

void SokobanLevel::CheckGameClear()
{
	// 타겟 위에 있는 박스의 수 검증.
	int currentScore = 0;

	// 배열에 박스 및 타겟 저장.
	std::vector<Ball*> ball;
	std::vector<Target*> targets;

	GetActorInstance<Ball>(ball);
	GetActorInstance<Target>(targets);

	if (ball.empty() || targets.empty())return;

	// 두 액터의 위치가 같으면 점수 +.
	if (ball[0]->TestIntersect(targets[0]))
	{
		score1 += 1;
	}
	else if(ball[0]->TestIntersect(targets[1]))
	{
		score2 += 1;
	}

}

void SokobanLevel::ShowScore()
{
	sprintf_s(scoreString1, 128, "Score: %d", score1);
	Renderer::Get().Submit(
		scoreString1,
		Vector2(0, 0)
	);
	sprintf_s(scoreString2, 128, "Score: %d", score2);
	Renderer::Get().Submit(
		scoreString2,
		Vector2(0, 1)
	);
}
