#include "CPowerUpItem.h"
#include "debug.h"

CPowerUpItem::CPowerUpItem(float x, float y) :CGameObject(x, y)
{
	this->isSuperLeaf = false;
	this->ay =	POWERUPITEM_GRAVITY;
	this->x_start = x;
	this->y_start = y;

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
	DebugOut(L"state: %d\n",state);
	DebugOut(L"y: %.8f\n",y);
	DebugOut(L"x: %.8f\n",x);
	DebugOut(L"ay: %.8f\n",ay);
	DebugOut(L"vy: %.8f\n",vy);
	vy += ay * dt;

	if ( state == POWERUPITEM_STATE_EATEN ) return;
	
	if ( state != POWERUPITEM_STATE_IDLE ) Moving();
	
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
		vy = -POWERUPITEM_SPEED * 2;
		ay = -POWERUPITEM_GRAVITY * 5;
		break;
	case POWERUPITEM_STATE_MOVING_LEFT:
		vx = -POWERUPITEM_SPEED*1.5;
		vy = POWERUPITEM_SPEED/3;
		ay = POWERUPITEM_GRAVITY;
		break;
	case POWERUPITEM_STATE_MOVING_RIGHT:
		vx = POWERUPITEM_SPEED*1.5;
		vy = POWERUPITEM_SPEED/3;
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
	DebugOut(L"y truoc: %.2f\n", y);
	y += vy * dt;
	DebugOut(L"y sau: %.2f\n", y);
};

void CPowerUpItem::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPowerUpItem*>(e->obj)) return;

	// Leaf doesn't reverse on collision
	if (isSuperLeaf == false)
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

void CPowerUpItem::Moving()
{
	if (isSuperLeaf == true)
	{
		if (state == POWERUPITEM_STATE_EMERGING && y <= y_start - POWERUPITEM_SUPERLEAF_EMERGE_HEIGHT)
		{
			SetState(POWERUPITEM_STATE_MOVING_RIGHT);
		}
		else if (state == POWERUPITEM_STATE_MOVING_RIGHT && x >= x_start + POWERUPITEM_SWING_WIDTH)
		{
			SetState(POWERUPITEM_STATE_MOVING_LEFT);
		}
		else if (state == POWERUPITEM_STATE_MOVING_LEFT && x <= x_start)
		{
			SetState(POWERUPITEM_STATE_MOVING_RIGHT);
		}
	}
	else
	{
		if (state == POWERUPITEM_STATE_EMERGING && y <= y_start - POWERUPITEM_SUPERMUSHROOM_EMERGE_HEIGHT)
		{
			SetState(POWERUPITEM_STATE_MOVING_RIGHT); //tam thoi nam di chuyen sang phai
		}
	}
	
}


