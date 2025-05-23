#pragma once
#include "GameObject.h"

#define ID_ANI_ITEMRANDOM_MUSHROOM 10000
#define ID_ANI_ITEMRANDOM_STAR 10001
#define ID_ANI_ITEMRANDOM_FLOWER 10001
#define ID_ANI_ITEMRANDOM_MUSHROOM_FLY 10001
#define ID_ANI_ITEMRANDOM_FLOWER_FLY 10001
#define ID_ANI_ITEMRANDOM_STAR_FLY 10001

#define ITEMRANDOM_BBOX_WIDTH 16
#define ITEMRANDOM_BBOX_HEIGHT 16

#define ITEMRANDOM_FLY_SPEED -0.2f
#define ITEMRANDOM_RANDOM_TIME 300


#define ITEMRANDOM_STATE_MUSHROOM 0
#define ITEMRANDOM_STATE_FLOWER 100
#define ITEMRANDOM_STATE_STAR 200
#define ITEMRANDOM_STATE_MUSHROOM_FLY 300
#define ITEMRANDOM_STATE_FLOWER_FLY 400
#define ITEMRANDOM_STATE_STAR_FLY 500

class CItemRanDom : public CGameObject
{
protected:
	ULONGLONG start_time;

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	void CheckAndChangeState();
public:
	CItemRanDom(float x, float y, int itemType) : CGameObject(x, y)
	{
		SetState(ITEMRANDOM_STATE_MUSHROOM);
	}
	void SetState(int state);
};

