#pragma once
#include "CKoopa.h"

#define PARAKOOPA_BOUNCE_SPEED -0.4f
#define PARAKOOPA_GRAVITY 0.02f

#define PARAKOOPA_STATE_WALKING_LEFT 10
#define PARAKOOPA_STATE_WALKING_RIGHT 11
#define PARAKOOPA_STATE_BOUNCE 12

#define ID_ANI_GREEN_PARAKOOPA_WALKING_LEFT 15020
#define ID_ANI_GREEN_PARAKOOPA_WALKING_RIGHT 15021

class CParaKoopa :public CKoopa
{
protected:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	boolean isKoopa;

	void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CParaKoopa(float x, float y, boolean isGreen);
	void SetState(int nextState);
	boolean GetIsKoomba() { return isKoopa; }
	void TurnIntoKoopa();
};

