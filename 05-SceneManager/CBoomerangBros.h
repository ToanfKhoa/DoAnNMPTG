#pragma once
#include "GameObject.h"

#define BOOMERANG_BROS_GRAVITY 0.0009f
#define BOOMERANG_BROS_WALKING_SPEED 0.025f
#define BOOMERANG_BROS_JUMP_SPEED 0.2f
#define BOOMERANG_BROS_BOUNCE_SPEED 0.1f

#define BOOMERANG_BROS_BBOX_WIDTH 16
#define BOOMERANG_BROS_BBOX_HEIGHT 20

#define BOOMERANG_BROS_STATE_WALKING 100
#define BOOMERANG_BROS_STATE_BOOMERANG_HOLDING 200
#define BOOMERANG_BROS_STATE_JUMP 300
#define BOOMERANG_BROS_STATE_BOUNCE_DEATH 0

#define ID_ANI_BOOMERANG_BROS_WALKING_LEFT 19000
#define ID_ANI_BOOMERANG_BROS_WALKING_RIGHT 19001
#define ID_ANI_BOOMERANG_BROS_HOLDING_LEFT 19002
#define ID_ANI_BOOMERANG_BROS_HOLDING_RIGHT 19003
#define ID_ANI_BOOMERANG_BROS_BOUNCE_DEATH 19004

#define MOVEMENT_OFFSET_X 10.0f

#define JUMP_DURATION	6200.0f
#define ATTACK_DURATION	 4000.0f
#define HOLDING_TIME 700.0f

class CBoomerangBros : public CGameObject
{
protected:
	float ax;
	float ay;
	float x_start;
	int direction_x;

	DWORD jumpTimer;
	DWORD attackTimer;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state != BOOMERANG_BROS_STATE_BOUNCE_DEATH; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsOverlappable() { return 1; };
	virtual void OnOverlapWith(LPCOLLISIONEVENT e);
	void OnOverlapWithBoomerang(LPCOLLISIONEVENT e);

public:
	CBoomerangBros(float x, float y);
	virtual void SetState(int state);
};

