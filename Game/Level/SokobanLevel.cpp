#include "SokobanLevel.h"
#include "Actor/Actor.h"
#include "Actor/Player1.h"
#include "Actor/Player2.h"
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
			AddNewActor(new Player1(position));
			AddNewActor(new Ground(position));
			break;

		case 'p':
			AddNewActor(new Player2(position));
			AddNewActor(new Ground(position));
			break;

		case '1':
			AddNewActor(new TeamMate("1", position, Color::Red,Vector2(80,5)));
			AddNewActor(new Ground(position));
			break;

		case '2':
			AddNewActor(new TeamMate("2", position, Color::Red, Vector2(68, 8)));
			AddNewActor(new Ground(position));
			break;

		case '3':
			AddNewActor(new TeamMate("3", position, Color::Red, Vector2(62, 24)));
			AddNewActor(new Ground(position));
			break;

		case '4':
			AddNewActor(new TeamMate("4", position, Color::Red, Vector2(75, 26)));
			AddNewActor(new Ground(position));
			break;
		case 's':
			AddNewActor(new TeamMate("1", position, Color::Green, Vector2(5, 80)));
			AddNewActor(new Ground(position));
			break;

		case 'h':
			AddNewActor(new TeamMate("2", position, Color::Green, Vector2(5, 80)));
			AddNewActor(new Ground(position));
			break;

		case 'i':
			AddNewActor(new TeamMate("3", position, Color::Green, Vector2(5, 80)));
			AddNewActor(new Ground(position));
			break;

		case 'n':
			AddNewActor(new TeamMate("4", position, Color::Green, Vector2(5, 80)));
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
  	std::vector<PlayerBase*> players;
  	std::vector<Ball*> balls;
  	std::vector<TeamMate*> teamMates;
  	GetActorInstance<Ball>(balls);
  	GetActorInstance<TeamMate>(teamMates);
  	GetActorInstance<PlayerBase>(players);
  	if (players.empty() || balls.empty() || teamMates.empty())
  		return;
  
  
  	for (Ball* const ball : balls)
  	{
  		PlayerBase* lastPlayer = ball->GetLastPlayer();
  		if (!lastPlayer) continue;

		for (PlayerBase* player : players)
		{
			if (!player) continue;
			if (player == ball->GetOwnActor()) continue;   // 이미 소유자면 스킵
			if (!ball->TestIntersect(player)) continue;

			ball->SetOwnActor(player);
			ball->SetLastPlayer(player);                  // 필요 없으면 이 줄 빼도 됨
			ball->setTp(ball->GetPosition(), ball->GetOwnActor()->GetPosition()); // 공 정지/타겟 초기화 의도면 유지
			break; // 플레이어 충돌 처리했으면 팀메이트 처리 넘어갈지 말지 정책에 따라 break/return
		}


  		for (TeamMate* const teamMate : teamMates)
  		{
			
  			if (!ball->TestIntersect(teamMate)) continue;
  			//팀원과 같은 색의 플레이어 찾기
  			PlayerBase* teamPlayer = nullptr;
  			for (PlayerBase* player : players)
  			{
  				if (player && player->GetColor() == teamMate->GetColor())
  				{
  					teamPlayer = player;
  					break;
  				}
  			}
  				if (teamPlayer == lastPlayer)
  				{	
  					//같은 팀 패스 공 : lastplayer <-> 팀원 스왑
  					Vector2 temp = lastPlayer->GetPosition();
  					lastPlayer->SetPosition(teamMate->GetPosition());
  					teamMate->SetPosition(temp);
  
  					ball->SetOwnActor(lastPlayer);
  				}
  				else
  				{
  					//상대 팀원 접촉 : 상대 플레이어 <-> 팀원 스왑 + 소유권 변경
  					Vector2 temp = teamPlayer->GetPosition();
  					teamPlayer->SetPosition(teamMate->GetPosition());
  					teamMate->SetPosition(temp);
  
  					ball->SetOwnActor(teamPlayer);
  				}
  			
  		}
  	}
  }

  bool SokobanLevel::CanMove(
	  const Wanted::Vector2& nextPosition)
  {
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
   //canmove
 
  }
	 

  void SokobanLevel::CheckGameClear()
  {
	  

	  // 배열에 박스 및 타겟 저장.
	  std::vector<Ball*> ball;
	  std::vector<Target*> targets;
	  std::vector<PlayerBase*> players;
	  std::vector<TeamMate*> teamMates;

	  GetActorInstance<Ball>(ball);
	  GetActorInstance<Target>(targets);
	  GetActorInstance<PlayerBase> (players);
	  GetActorInstance<TeamMate>(teamMates);

	  if (ball.empty() || targets.empty()||teamMates.empty()||players.empty())return;

	  // 두 액터의 위치가 같으면 점수 +.
	  if (ball[0]->TestIntersect(targets[0]))
	  {
		  score1 += 1;
		  ball[0]->SetOwnActor(players[0]);
		  for (TeamMate* tm : teamMates)
		  {
			  tm->setTp(tm->GetH(), tm->GetA());
		  }
	  }
	  else if (ball[0]->TestIntersect(targets[1]))
	  {
		  score2 += 1;
		  ball[0]->SetOwnActor(players[1]);
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
