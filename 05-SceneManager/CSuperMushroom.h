#pragma once
#include "GameObject.h"

#define SUPERMUSHROOM_GRAVITY 0.002f
#define SUPERMUSHROOM_SPEED 0.05f


#define SUPERMUSHROOM_BBOX_WIDTH 16
#define SUPERMUSHROOM_BBOX_HEIGHT 16

#define SUPERMUSHROOM_STATE_IDLE 0
#define SUPERMUSHROOM_STATE_EMERGING     100
#define SUPERMUSHROOM_STATE_MOVING       200
#define SUPERMUSHROOM_STATE_EATEN        300

#define ID_ANI_SUPERMUSHROOM 13000

class CSuperMushroom :public CGameObject
{
protected:
	float ay;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return (state != SUPERMUSHROOM_STATE_IDLE && state!=SUPERMUSHROOM_STATE_EATEN); };
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CSuperMushroom(float x, float y);
	void SetState(int state);
};

