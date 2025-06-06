#pragma once
#include "GameObject.h"
#include "Game.h"
#include "PlayScene.h"

#define SPRITE_BLUR_EYE_CLOUD	102019
#define SPRITE_EYE_CLOUD_FULL	102009
#define SPRITE_EYE_CLOUD_MIDDLE	102010
#define SPRITE_EYE_CLOUD_RIGHTHALF	102011

#define ID_SPRITE_ITEMRANDOM_MUSHROOM_WHITE	84101
#define ID_SPRITE_ITEMRANDOM_FLOWER_WHITE 84103
#define ID_SPRITE_ITEMRANDOM_STAR_WHITE	84105

#define SPRITE_SPIRAL_CLOUD_SMALL 102012
#define SPRITE_SPIRAL_CLOUD_BIG	102013

class CDecoration : public CGameObject
{
protected:
	int spriteId;
public:
	CDecoration(float x, float y, int spriteId) : CGameObject(x, y)
	{
		this->spriteId = spriteId;
		
		if (spriteId == SPRITE_EYE_CLOUD_FULL || spriteId == SPRITE_EYE_CLOUD_MIDDLE || spriteId == SPRITE_EYE_CLOUD_RIGHTHALF || spriteId == SPRITE_SPIRAL_CLOUD_BIG || spriteId == SPRITE_SPIRAL_CLOUD_SMALL)
			this->layer = -10;
		else if (spriteId == SPRITE_BLUR_EYE_CLOUD 
			|| spriteId == ID_SPRITE_ITEMRANDOM_MUSHROOM_WHITE || spriteId == ID_SPRITE_ITEMRANDOM_FLOWER_WHITE || spriteId == ID_SPRITE_ITEMRANDOM_STAR_WHITE)
			this->layer = -11;

		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

