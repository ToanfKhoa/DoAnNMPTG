#pragma once
#include "GameObject.h"
#include "CNumber.h"
#include "Game.h"
#include "PlayScene.h"
class CNumber;
typedef CNumber* LPNUMBER;

#define SPRITE_POWER_ACTIVE 120020
#define SPRITE_FULL_POWER 120021

class CHeadsUpDisplay :public CGameObject
{
protected:
	int spriteId;
	LPNUMBER numberCoin;
	LPNUMBER numberPoint;
	LPNUMBER numberTime;

public:
	CHeadsUpDisplay(float x, float y, int spriteId) : CGameObject(x, y)
	{
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		this->spriteId = spriteId;
		numberCoin = new CNumber(x - 10, y - 16, 2);
		numberTime = new CNumber(x - 10, y - 8, 3);
		numberPoint = new CNumber(x - 62, y - 8, 7);
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

