#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class CourtLevel 
	: public Wanted::Level, 
	public ICanPlayerMove
{
	RTTI_DECLARATIONS(CourtLevel, Level)

public:
	CourtLevel();

	// 이벤트 함수 오버라이드.
	virtual void Draw() override;
	
private:

	// 게임에서 사용할 맵을 로드하는 함수.
	void LoadMap(const char* filename);
	virtual void Tick(float deltaTime) override;

	//Teammate <-> Player 포지션 변경
	void ChangePosition();

	// Inherited via ICanPlayerMove
	virtual bool CanMove(const Wanted::Vector2& nextPosition) override;

	// 게임 클리어 확인 함수.
	void ScoreSet();

	// 점수 보여주는 함수.
	void ShowScore();

private:
	//공수 변경
	int lastScoringTeam = 0;

	//점수 변수
	int score1 = 0;
	int score2 = 0;

	// 게임 클리어 여부를 알려주는 변수.
	bool isGameClear = false;

	char scoreString1[128] = {};
	char scoreString2[128] = {};
};
