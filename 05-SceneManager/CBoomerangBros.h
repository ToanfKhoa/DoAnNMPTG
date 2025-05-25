#pragma once
#include "GameObject.h"

#define BOOMERANG_BROS_GRAVITY 0.002f
#define BOOMERANG_BROS_WALKING_SPEED 0.035f
#define BOOMERANG_BROS_BOUNCE_SPEED 0.05f

#define BOOMERANG_BROS_BBOX_WIDTH 16
#define BOOMERANG_BROS_BBOX_HEIGHT 24

#define BOOMERANG_BROS_STATE_WALKING 100
#define BOOMERANG_BROS_STATE_BOOMERANG_HOLDING 200
#define BOOMERANG_BROS_STATE_JUMP 300
#define BOOMERANG_BROS_STATE_BOUNCE_DEATH 0

#define ID_ANI_BOOMERANG_BROS_WALKING_LEFT 6000
#define ID_ANI_BOOMERANG_BROS_HOLDING_LEFT 6001
#define ID_ANI_BOOMERANG_BROS_WALKING_RIGHT 6002
#define ID_ANI_BOOMERANG_BROS_HOLDING_RIGHT 6003
#define ID_ANI_BOOMERANG_BROS_BOUNCE_DEATH 6004

#define ID_MOVEMENT_OFFSET_X 10.0f	
class CBoomerangBros : public CGameObject
{
protected:
	float ax;
	float ay;
	float x_start;
	int direction_x;
	bool isHolding;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state != BOOMERANG_BROS_STATE_BOUNCE_DEATH; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBoomerangBros(float x, float y);
	virtual void SetState(int state);
};

