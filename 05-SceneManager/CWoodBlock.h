#pragma once
#include "GameObject.h"

#define WOODBLOCK_BBOX_WIDTH 16
#define WOODBLOCK_BBOX_HEIGHT 16

#define ID_ANI_WOODBLOCK 16000
#define ID_SPRITE_WOODBLOCK 20010

class CWoodBlock : public CGameObject
{
public:
	CWoodBlock(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

