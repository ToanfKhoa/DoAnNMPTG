#include "CParaKoopa.h"

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isKoopa)
	{
		CKoopa::Update(dt, coObjects);
		return;
	}

	vy += ay * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParaKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (isKoopa)
	{
		CKoopa::OnCollisionWith(e);
	}

	if (!e->obj->IsBlocking()) return;


	if (e->ny != 0) //bounce
	{
		vy = PARAKOOPA_BOUNCE_SPEED;
	}
	else if (e->nx != 0)
	{
		if (state == PARAKOOPA_STATE_WALKING_LEFT) SetState(KOOPA_STATE_WALKING_RIGHT);
		else if (state == PARAKOOPA_STATE_WALKING_RIGHT) SetState(KOOPA_STATE_WALKING_LEFT);
	}
}

CParaKoopa::CParaKoopa(float x, float y, boolean isGreen): CKoopa(x,y,isGreen)
{
	this->ay = PARAKOOPA_GRAVITY;
	boolean isKoopa = false;
	SetState(PARAKOOPA_STATE_WALKING_LEFT);
}

void CParaKoopa::SetState(int nextState)
{
	if (isKoopa)
	{
		CKoopa::SetState(state);
		return;
	}

	switch (nextState)
	{
	case PARAKOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		isFlipped = false; //koopa wakes up and returns to normal
		break;

	case PARAKOOPA_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		isFlipped = false; //koopa wakes up and returns to normal
		break;
	}
	CGameObject::SetState(nextState); //need to update state later to check current state
}

