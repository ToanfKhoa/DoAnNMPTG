#pragma once
#include "GameObject.h"

#define	EXTRALIFEMUSHROOM_GRAVITY 0.00005f
#define EXTRALIFEMUSHROOM_SPEED 0.05f
#define EXTRALIFEMUSHROOM_EMERGE_HEIGHT 16

#define EXTRALIFEMUSHROOM_BBOX_WIDTH 16
#define EXTRALIFEMUSHROOM_BBOX_HEIGHT 14

#define EXTRALIFEMUSHROOM_STATE_IDLE 0
#define EXTRALIFEMUSHROOM_STATE_EMERGING 100
#define EXTRALIFEMUSHROOM_STATE_MOVING_LEFT 200
#define EXTRALIFEMUSHROOM_STATE_MOVING_RIGHT 300
#define EXTRALIFEMUSHROOM_STATE_EATEN 400

class CExtraLifeMushroom : public CGameObject
{
protected:
	float ay;
	float y_start;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }


	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void CheckAndChangeState();

public:
	CExtraLifeMushroom(float x, float y);
	void SetState(int state);
};

