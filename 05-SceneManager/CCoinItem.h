#pragma once
#include "GameObject.h"

#define ID_ANI_COINITEM 14000

#define	COINITEM_WIDTH 10
#define COINITEM_BBOX_WIDTH 10
#define COINITEM_BBOX_HEIGHT 16

#define COINITEM_STATE_IDLE 0
#define COINITEM_STATE_BOUNCING_UP 1
#define COINITEM_STATE_BOUNCING_DOWN 2

#define COINITEM_BOUNCE_SPEED 0.2f
#define COINITEM_BOUNCE_HEIGHT 64
#define COINITEM_BOUNCE_DELETE_HEIGHT 24


class CCoinItem :public CGameObject
{
	float y_start;
public:
	CCoinItem(float x, float y) : CGameObject(x, y) 
	{
		y_start = y;
		state = COINITEM_STATE_IDLE;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

