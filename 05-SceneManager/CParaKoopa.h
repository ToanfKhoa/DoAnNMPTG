#pragma once
#include "CKoopa.h"

#define PARAKOOPA_WALKING_SPEED 0.03f
#define PARAKOOPA_BOUNCE_SPEED -0.22f
#define PARAKOOPA_GRAVITY 0.0005f

#define PARAKOOPA_STATE_WALKING_LEFT 10
#define PARAKOOPA_STATE_WALKING_RIGHT 11
#define PARAKOOPA_STATE_BOUNCE 12
#define PARAKOOPA_STATE_FLY_UP_DOWN 13

#define ID_ANI_GREEN_PARAKOOPA_WALKING_LEFT 15020
#define ID_ANI_GREEN_PARAKOOPA_WALKING_RIGHT 15021

#define ID_ANI_RED_PARAKOOPA_WALKING_LEFT 15022

#define FLY_UP_DOWN_OFFSET 80
class CParaKoopa :public CKoopa
{
protected:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	boolean isKoopa;
	float y_start;

	int IsCollidable() 
	{ 
		if (!isKoopa) return 1;
		else CKoopa::IsCollidable(); 
	}
	int IsOverlappable() 
	{ 
		if (!isKoopa) return 0;
		else CKoopa::IsOverlappable();
	}

	void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CParaKoopa(float x, float y, boolean isGreen);
	void SetState(int nextState);
	boolean GetIsKoopa() { return isKoopa; }
	void TurnIntoKoopa();
};

