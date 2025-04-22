#pragma once
#include "GameObject.h"

#define ID_ANI_QUESTIONBLOCK 12000
#define ID_ANI_QUESTIONBLOCK_USED 12001

#define QUESTIONBLOCK_WIDTH 16
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16

#define QUESTIONBLOCK_ITEM_TYPE_COIN 0
#define QUESTIONBLOCK_ITEM_TYPE_POWERUP 1

#define QUESTIONBLOCK_BOUNCING_SPEED 0.1
#define QUESTIONBLOCK_BOUNCE_HEIGTH 5


#define QUESTIONBLOCK_STATE_IDLE 0
#define QUESTIONBLOCK_STATE_BOUNCING_UP 100
#define QUESTIONBLOCK_STATE_BOUNCING_DOWN 200
#define QUESTIONBLOCK_STATE_USED 300

class CQuestionBlock :public CGameObject
{
protected:
	float y_start;
	int itemType;	//0 coin, 1 powerup
	CGameObject* spawnedItem;

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void OnNoCollision(DWORD dt);

	void Bouncing();
	void ActivatePowerUpItem();
	void ActivateCoinItem();
public:
	CQuestionBlock(float x, float y, int itemType);
	void SetState(int state);
};

