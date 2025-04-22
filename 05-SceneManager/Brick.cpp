#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if(state == BRICK_STATE_IDLE) animations->Get(ID_ANI_BRICK)->Render(x, y);
	else animations->Get(ID_ANI_BRICK_USED)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state != BRICK_STATE_USED && state != BRICK_STATE_BROKEN)
	{
		Bouncing();

		CCollision::GetInstance()->Process(this, dt, coObjects);
	}

	CGameObject::Update(dt, coObjects);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CBrick::Bouncing()
{
	if (state == BRICK_STATE_BOUNCING_UP)
	{
		if (y <= y_start - BRICK_BOUNCE_HEIGHT)
		{
			y = y_start - BRICK_BOUNCE_HEIGHT;
			SetState(BRICK_STATE_BOUNCING_DOWN);
		}
	}

	else if (GetState() == BRICK_STATE_BOUNCING_DOWN)
	{
		if (y >= y_start)
		{
			y = y_start;
			SetState(BRICK_STATE_USED);
		}
	}
}

CBrick::CBrick(float x, float y) : CGameObject(x, y) 
{
	this->x = x;
	this->y = y;
	y_start = y;
	SetState(BRICK_STATE_IDLE);
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_USED:
		vy = 0;
		break;
	case BRICK_STATE_IDLE:
		vy = 0;
		break;
	case BRICK_STATE_BOUNCING_UP:
		vy = -BRICK_BOUNCING_SPEED;
		break;
	case BRICK_STATE_BOUNCING_DOWN:
		vy = BRICK_BOUNCING_SPEED;
		break;
	}
}
