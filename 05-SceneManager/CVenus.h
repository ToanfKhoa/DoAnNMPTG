#pragma once
#include "GameObject.h"

#define VENUS_SPEED 0.05f

#define VENUS_BBOX_WIDTH 20
#define VENUS_BBOX_HEIGHT 40

#define VENUS_STATE_HIDE 100
#define VENUS_STATE_UP 200
#define VENUS_STATE_DOWN 300
#define VENUS_STATE_FIRE 400
#define VENUS_STATE_DIE 500

#define ID_ANI_VENUS_TOPLEFT 5000
#define ID_ANI_VENUS_BOTLEFT 5001
#define ID_ANI_VENUS_TOPRIGHT 5002
#define ID_ANI_VENUS_BOTRIGHT 5003
#define ID_ANI_VENUS_DIE 5004

#define VENUS_HIDE_TIME 1000
#define VENUS_APPEAR_TIME 1000
#define VENUS_MOVE_TIME 1000

class CVenus : public CGameObject
{
protected:
	int direction_x;
	int direction_y;

	DWORD timer;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CVenus(float x, float y);
	virtual void SetState(int state);
	void UpAndDown(DWORD dt);
};

