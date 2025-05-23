#pragma once
#include "GameObject.h"

#define WOODBAR_HEIGHT 16
#define WOODBAR_WIDTH 54
#define WOODBAR_SPEED_X 0.01f
#define WOODBAR_SPEED_Y 0.01f

#define ID_SPRITE_WOODBAR_START	20020
#define ID_SPRITE_WOODBAR_MIDDLE 20021
#define ID_SPRITE_WOODBAR_END 20022

#define SPRITE_SPACING 16
class CWoodBar : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 2; } //Only blocking mario

public:
	CWoodBar(float x, float y) : CGameObject(x, y) { vx = -WOODBAR_SPEED_X; };
	void Fall();
};

