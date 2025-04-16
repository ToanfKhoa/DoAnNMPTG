#include "CPowerUpItem.h"

CPowerUpItem::CPowerUpItem(float x, float y) :CGameObject(x, y)
{
	this->isSuperLeaf = false;
	this->ay =	POWERUPITEM_GRAVITY;
	SetState(POWERUPITEM_STATE_IDLE);
}

void CPowerUpItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - POWERUPITEM_BBOX_WIDTH / 2;
	top = y - POWERUPITEM_BBOX_HEIGHT / 2;
	right = left + POWERUPITEM_BBOX_WIDTH;
	bottom = top + POWERUPITEM_BBOX_HEIGHT;
}
void CPowerUpItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if ((state == POWERUPITEM_STATE_EATEN))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPowerUpItem::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == POWERUPITEM_STATE_IDLE) return;
	else if (isSuperLeaf == true)
	{
		if( state==POWERUPITEM_STATE_MOVING_LEFT || state == POWERUPITEM_STATE_EMERGING)
			aniId = ID_ANI_SUPERLEAF_LEFT;
		else 
			aniId = ID_ANI_SUPERLEAF_RIGHT;
	}
	else 
		aniId = ID_ANI_SUPERMUSHROOM;

	animations->Get(aniId)->Render(x, y);

}

void CPowerUpItem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case POWERUPITEM_STATE_IDLE:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case POWERUPITEM_STATE_EMERGING:
	    vx = 0;
		vy = -POWERUPITEM_GRAVITY;
		ay = 0;
		break;
	case POWERUPITEM_STATE_MOVING_LEFT:
	case POWERUPITEM_STATE_MOVING_RIGHT:
		vx = POWERUPITEM_SPEED;
		vy = POWERUPITEM_GRAVITY;
		ay = POWERUPITEM_GRAVITY;
		break;
	case POWERUPITEM_STATE_EATEN:
		vx = 0;
		vy = 0;
		ay = 0;
		isDeleted = true;
		break;
	}
}

void CPowerUpItem::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPowerUpItem::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPowerUpItem*>(e->obj)) return;

	// Leaf doesn't reverse on collision
	if (isSuperLeaf = false)
	{
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
	
}


