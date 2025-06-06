#pragma once
#include "GameObject.h"
#include "Game.h"
#include "PlayScene.h"

#define SPRITE_BLUR_EYE_CLOUD	102019
#define SPRITE_EYE_CLOUD_FULL	102009
#define SPRITE_EYE_CLOUD_MIDDLE	102010
#define SPRITE_EYE_CLOUD_RIGHTHALF	102011

class CDecoration : public CGameObject
{
protected:
	int spriteId;
public:
	CDecoration(float x, float y, int spriteId) : CGameObject(x, y)
	{
		this->spriteId = spriteId;
		
		if (spriteId == SPRITE_EYE_CLOUD_FULL || spriteId == SPRITE_EYE_CLOUD_MIDDLE || spriteId == SPRITE_EYE_CLOUD_RIGHTHALF)
			SetLayer(-10);
		else if (spriteId == SPRITE_BLUR_EYE_CLOUD)
			SetLayer(-11);

		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		playScene->SortObjects();
	}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

