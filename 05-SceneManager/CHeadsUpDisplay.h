#pragma once
#include "GameObject.h"
#include "CNumber.h"
#include "Game.h"
#include "PlayScene.h"
#include "AssetIDs.h"

class CNumber;
typedef CNumber* LPNUMBER;

#define SPRITE_POWER_ACTIVE 120020
#define SPRITE_FULL_POWER 120021

#define SPRITE_CARD_MUSHROOM 120027
#define SPRITE_CARD_FLOWER 120028
#define SPRITE_CARD_STAR 120029

class CHeadsUpDisplay :public CGameObject
{
protected:
	int spriteId;
	LPNUMBER numberCoin;
	LPNUMBER numberPoint;
	LPNUMBER numberTime;
	LPNUMBER numberLives;

public:
	CHeadsUpDisplay(float x, float y, int spriteId) : CGameObject(x, y)
	{
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		this->spriteId = spriteId;
		numberCoin = new CNumber(x - 10, y - 16, 2);
		numberTime = new CNumber(x - 10, y - 8, 3);
		numberPoint = new CNumber(x - 62, y - 8, 7);
		numberLives = new CNumber(x - 140, y - 8, 1);
		this->layer = HUD_LAYER;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

