#pragma once
#include "GameObject.h"
#include "debug.h"
#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.035f
#define KOOPA_BOUNCE_SPEED 0.4f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_BOUNCE_DEATH 0

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_BOUNCE_DEATH 5002

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	BOOLEAN isOnPlatform;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state != GOOMBA_STATE_BOUNCE_DEATH; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);
};