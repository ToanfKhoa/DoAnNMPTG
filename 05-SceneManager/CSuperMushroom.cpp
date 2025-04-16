#include "CSuperMushroom.h"

void CSuperMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SUPERMUSHROOM_BBOX_WIDTH / 2;
	top = y - SUPERMUSHROOM_BBOX_HEIGHT / 2;
	right = left + SUPERMUSHROOM_BBOX_WIDTH;
	bottom = top + SUPERMUSHROOM_BBOX_HEIGHT;
}
void CSuperMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if ((state == SUPERMUSHROOM_STATE_EATEN))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CSuperMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SUPERMUSHROOM_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case SUPERMUSHROOM_STATE_EMERGING:
	    vx = 0;
		vy = -SUPERMUSHROOM_GRAVITY;
		break;
	case SUPERMUSHROOM_STATE_MOVING:
		vx = SUPERMUSHROOM_SPEED;
		vy = SUPERMUSHROOM_GRAVITY;
		break;
	case SUPERMUSHROOM_STATE_EATEN:
		vx = 0;
		vy = 0;
		isDeleted = true;
		break;
	}
}

void CSuperMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CSuperMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CSuperMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}


