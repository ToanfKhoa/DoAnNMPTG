#pragma once
#include "GameObject.h"

#define	EXTRALIFEMUSHROOM_GRAVITY 0.00005f
#define EXTRALIFEMUSHROOM_SPEED 0.05f
#define EXTRALIFEMUSHROOM_EMERGE_HEIGHT 16

class CExtraLifeMushroom : public CGameObject
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

	void CheckAndChangeState();

public:
	CExtraLifeMushroom(float x, float y);
	void SetState(int state);
};

