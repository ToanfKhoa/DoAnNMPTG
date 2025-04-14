#include "CVenus.h"
#include "debug.h"

CVenus::CVenus(float x, float y) :CGameObject(x, y)
{
	SetState(VENUS_STATE_HIDE);
	timer = 0;
}

void CVenus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VENUS_BBOX_WIDTH / 2;
	top = y - VENUS_BBOX_HEIGHT / 2;
	right = left + VENUS_BBOX_WIDTH;
	bottom = top + VENUS_BBOX_HEIGHT;
}

void CVenus::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CVenus::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

}

void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//die
	if (this->GetState() == VENUS_STATE_DIE)
	{
		isDeleted = true;
		return;
	}

	UpAndDown(dt);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CVenus::Render()
{
	int aniId = ID_ANI_VENUS_TOPLEFT;
	
	//Set animation based on direction
	if (state == VENUS_STATE_DIE)
	{
		aniId = ID_ANI_VENUS_DIE;
	}
	else if(direction_x == -1 && direction_y == -1) 	
	{
		aniId = ID_ANI_VENUS_TOPLEFT;
	}
	else if (direction_x == -1 && direction_y == 1)
	{
		aniId = ID_ANI_VENUS_BOTLEFT;
	}
	else if (direction_x == 1 && direction_y == -1)
	{
		aniId = ID_ANI_VENUS_TOPRIGHT;
	}
	else if (direction_x == 1 && direction_y == 1)
	{
		aniId = ID_ANI_VENUS_BOTRIGHT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CVenus::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUS_STATE_HIDE:
		vx = 0;
		vy = 0;
		break;
	case VENUS_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case VENUS_STATE_UP:
		vy = -VENUS_SPEED;
		break;
	case VENUS_STATE_DOWN:
		vy = VENUS_SPEED;
		break;
	case VENUS_STATE_FIRE:
		vy = 0;
		break;
	}
}

void CVenus::UpAndDown(DWORD dt)
{
	timer += dt;

	if (timer < VENUS_HIDE_TIME)
		SetState(VENUS_STATE_HIDE);
	else if (timer < VENUS_HIDE_TIME + VENUS_MOVE_TIME)
		SetState(VENUS_STATE_UP);
	else if (timer < VENUS_HIDE_TIME + VENUS_MOVE_TIME + VENUS_APPEAR_TIME)
		SetState(VENUS_STATE_FIRE);
	else if (timer < VENUS_HIDE_TIME + 2 * VENUS_MOVE_TIME + VENUS_APPEAR_TIME)
		SetState(VENUS_STATE_DOWN);
	else
		timer = 0;
}