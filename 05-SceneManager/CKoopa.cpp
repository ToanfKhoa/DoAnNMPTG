#include "CKoopa.h"

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_WALKING_LEFT && state == KOOPA_STATE_WALKING_RIGHT)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_SHELL_WIDTH / 2;
		top = y - KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + KOOPA_BBOX_SHELL_WIDTH;
		bottom = top + KOOPA_BBOX_SHELL_HEIGHT;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (state == KOOPA_STATE_DIE)
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (state == KOOPA_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if (state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_BEING_HELD)
	{
		aniId = ID_ANI_KOOPA_SHELL_IDLE;
	}
	else if (state == KOOPA_STATE_SHELL_MOVING)
	{
		aniId = ID_ANI_KOOPA_SHELL_MOVING;
	}
	else if (state == KOOPA_STATE_SHELL_REVIVE)
	{
		aniId = ID_ANI_KOOPA_SHELL_REVIVE;
	}
	else if (state == KOOPA_STATE_BEING_HELD)
	{
		aniId = ID_ANI_KOOPA_SHELL_IDLE;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_SHELL_IDLE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

CKoopa::CKoopa(float x, float y)
{
	this->x = x;
	this->y = y;
	vx = KOOPA_WALKING_SPEED;
	ay = KOOPA_GRAVITY;
	SetState(KOOPA_STATE_WALKING_LEFT);
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
}
