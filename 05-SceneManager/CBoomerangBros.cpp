#include "CBoomerangBros.h"
#include "CBoomerangBros.h"

CBoomerangBros::CBoomerangBros(float x, float y) :CGameObject(x, y)
{
	this->ay = BOOMERANG_BROS_GRAVITY;
	vx = -BOOMERANG_BROS_WALKING_SPEED;
	SetState(BOOMERANG_BROS_STATE_WALKING);
	x_start = x;
	direction_x = -1; // Default direction is left
	isHolding = true; // Initially holding the boomerang
}

void CBoomerangBros::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BOOMERANG_BROS_BBOX_WIDTH / 2;
	top = y - BOOMERANG_BROS_BBOX_HEIGHT / 2;
	right = left + BOOMERANG_BROS_BBOX_WIDTH;
	bottom = top + BOOMERANG_BROS_BBOX_HEIGHT;
}

void CBoomerangBros::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBoomerangBros::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
}

void CBoomerangBros::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if(x > x_start)
	{
		direction_x = -1; // Change direction to left
		vx = -BOOMERANG_BROS_WALKING_SPEED;
	}
	else if(x < x_start - ID_MOVEMENT_OFFSET_X)
	{
		direction_x = 1; // Change direction to right
		vx = BOOMERANG_BROS_WALKING_SPEED;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBoomerangBros::Render()
{
	int aniId = ID_ANI_BOOMERANG_BROS_WALKING_LEFT;
	
	if (state == BOOMERANG_BROS_STATE_BOUNCE_DEATH)
	{
		aniId = ID_ANI_BOOMERANG_BROS_BOUNCE_DEATH;
	}
	else if (state == BOOMERANG_BROS_STATE_BOOMERANG_HOLDING)
	{
		if (direction_x > 0)
			aniId = ID_ANI_BOOMERANG_BROS_WALKING_RIGHT; // Holding boomerang while walking right
		else
			aniId = ID_ANI_BOOMERANG_BROS_WALKING_LEFT; // Holding boomerang while walking left
	}
	else if (state == BOOMERANG_BROS_STATE_WALKING)
	{
		if (direction_x > 0)
			aniId = ID_ANI_BOOMERANG_BROS_WALKING_RIGHT;
		else
			aniId = ID_ANI_BOOMERANG_BROS_WALKING_LEFT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBoomerangBros::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_BROS_STATE_WALKING:
		vx = direction_x *BOOMERANG_BROS_WALKING_SPEED;
		break;
	case BOOMERANG_BROS_STATE_BOOMERANG_HOLDING:
		isHolding = true;
		break;
	case BOOMERANG_BROS_STATE_JUMP:
		vy = -BOOMERANG_BROS_BOUNCE_SPEED; // Set initial jump speed
		ay = BOOMERANG_BROS_GRAVITY; // Apply gravity during the jump
		break;
	case BOOMERANG_BROS_STATE_BOUNCE_DEATH:
		vy = -BOOMERANG_BROS_BOUNCE_SPEED;
		ay = BOOMERANG_BROS_GRAVITY;
		break;
	}
}