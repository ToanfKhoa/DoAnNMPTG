#pragma once
#include "GameObject.h"

#define	POWERUPITEM_GRAVITY 0.00005f
#define POWERUPITEM_SPEED 0.05f
#define POWERUPITEM_SWING_WIDTH 32
#define POWERUPITEM_SUPERLEAF_EMERGE_HEIGHT 40
#define POWERUPITEM_SUPERMUSHROOM_EMERGE_HEIGHT 24

#define POWERUPITEM_BBOX_WIDTH 16
#define POWERUPITEM_BBOX_HEIGHT 16

#define POWERUPITEM_STATE_IDLE 0
#define POWERUPITEM_STATE_EMERGING 100
#define POWERUPITEM_STATE_MOVING_LEFT 200
#define POWERUPITEM_STATE_MOVING_RIGHT 300
#define POWERUPITEM_STATE_EATEN 400

#define ID_ANI_SUPERMUSHROOM 13000

#define ID_ANI_SUPERLEAF_LEFT 13100
#define ID_ANI_SUPERLEAF_RIGHT 13200

class CPowerUpItem :public CGameObject
{
protected:
	float ay;
	bool isSuperLeaf;
	float x_start;
	float y_start;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return !isSuperLeaf; }; 
	int IsBlocking() { return 0; }


	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void Moving();

public:
	CPowerUpItem(float x, float y);
	void SetState(int state);
};

