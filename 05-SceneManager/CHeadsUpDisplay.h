#pragma once
#include "GameObject.h"
#include "CNumber.h"
#include "Game.h"
#include "PlayScene.h"
class CNumber;
typedef CNumber* LPNUMBER;

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
		numberCoin = new CNumber(x, y - 60, 2);
		numberTime = new CNumber(x, y - 50, 3);
		numberPoint = new CNumber(x, y - 40, 7);
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

