#pragma once
#include "GameObject.h"

#define ID_ANI_COINITEM 14000

#define	COINITEM_WIDTH 10
#define COINITEM_BBOX_WIDTH 10
#define COINITEM_BBOX_HEIGHT 16

class CCoinItem :public CGameObject
{
public:
	CCoinItem(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

