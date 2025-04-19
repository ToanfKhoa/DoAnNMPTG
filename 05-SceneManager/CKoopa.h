#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_SHELL_WIDTH 16
#define KOOPA_BBOX_SHELL_HEIGHT 16

#define KOOPA_STATE_WALKING_LEFT 0
#define KOOPA_STATE_WALKING_RIGHT 1
#define KOOPA_STATE_SHELL_IDLE 2
#define KOOPA_STATE_SHELL_MOVING 2
#define KOOPA_STATE_SHELL_REVIVE 3
#define KOOPA_STATE_BEING_HELD 4
#define KOOPA_STATE_DIE 5

#define ID_ANI_KOOPA_WALKING_LEFT 15000
#define ID_ANI_KOOPA_WALKING_RIGHT 15001
#define ID_ANI_KOOPA_SHELL_IDLE 15002
#define ID_ANI_KOOPA_SHELL_MOVING 15003
#define ID_ANI_KOOPA_SHELL_REVIVE 15004

class CKoopa :public CGameObject
{
protected:
	float ay;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; }

	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y);
	void SetState(int state);
};

