#pragma once
#include "GameObject.h"

#define	POWERUPITEM_GRAVITY 0.002f
#define POWERUPITEM_SPEED 0.05f


#define POWERUPITEM_BBOX_WIDTH 16
#define POWERUPITEM_BBOX_HEIGHT 16

#define POWERUPITEM_STATE_IDLE 0
#define POWERUPITEM_STATE_EMERGING     100
#define POWERUPITEM_STATE_MOVING_LEFT       200
#define POWERUPITEM_STATE_MOVING_RIGHT       300
#define POWERUPITEM_STATE_EATEN        400

#define ID_ANI_SUPERMUSHROOM 13000

#define ID_ANI_SUPERLEAF_LEFT 13100
#define ID_ANI_SUPERLEAF_RIGHT 13200

class CPowerUpItem :public CGameObject
{
protected:
	float ay;
	bool isSuperLeaf;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return (state != POWERUPITEM_STATE_IDLE && state!= POWERUPITEM_STATE_EATEN); };
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPowerUpItem(float x, float y);
	void SetState(int state);
};

