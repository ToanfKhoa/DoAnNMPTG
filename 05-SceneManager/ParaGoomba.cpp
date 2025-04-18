#include "ParaGoomba.h"
#include "debug.h"

CParaGoomba::CParaGoomba(float x, float y) : CGoomba(x, y)
{
	this->ax = 0;
	this->ay = PARAGOOMBA_GRAVITY;
	die_start = -1;
	isGoomba = false;
	SetState(PARAGOOMBA_STATE_WALKING);
	vx = -PARAGOOMBA_WALKING_SPEED;
	fly_start = GetTickCount64();
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isGoomba == false)
	{
		vy += ay * dt;
		vx += ax * dt;

		//Fly if it's ParaGoomba
		Flying();

		if (state == GOOMBA_STATE_DIE)
		{
			isDeleted = true;
			return;
		}

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	else
		CGoomba::Update(dt, coObjects);
}


void CParaGoomba::Render()
{
	int aniId = ID_ANI_PARAGOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	if (isGoomba == false)
	{
		CGameObject::SetState(state);
		switch (state)
		{
		//ParaGoomba not affected by gravity while flying
		case PARAGOOMBA_STATE_FLYING_UP:
			vy = -PARAGOOMBA_FLYING_SPEED;
			ay = 0;
			break;
		case PARAGOOMBA_STATE_FLYING_DOWN:
			vy = PARAGOOMBA_FLYING_SPEED;
			ay = 0;
			break;
		case PARAGOOMBA_STATE_WALKING:
			break;
		}
	}
	else
	{
		CGoomba::SetState(state);
	}
}

//Check if the time is up and set flying state, this is called in update
void CParaGoomba::Flying()
{
	if(state == PARAGOOMBA_STATE_WALKING && GetTickCount64() - fly_start >= PARAGOOMBA_FLY_PERIOD)
	{
		SetState(PARAGOOMBA_STATE_FLYING_UP);
		fly_start = GetTickCount64();
	}

	else if(state == PARAGOOMBA_STATE_FLYING_UP && GetTickCount64() - fly_start >= PARAGOOMBA_FLY_TIME / 2)
	{
		SetState(PARAGOOMBA_STATE_FLYING_DOWN);
		fly_start = GetTickCount64();
	}

	else if (state != PARAGOOMBA_STATE_WALKING && GetTickCount64() - fly_start >= PARAGOOMBA_FLY_TIME)
	{
		SetState(PARAGOOMBA_STATE_WALKING);
		fly_start = GetTickCount64();
	}
}

void CParaGoomba::TurnIntoGoomba()
{
	isGoomba = true;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	SetState(GOOMBA_STATE_WALKING);
}
