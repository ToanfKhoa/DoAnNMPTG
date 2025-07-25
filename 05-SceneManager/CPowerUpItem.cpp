#include "CPowerUpItem.h"
#include "PlayScene.h"
#include "debug.h"
#include "AssetIDs.h"

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
	vy += ay * dt;

	if ( state == POWERUPITEM_STATE_EATEN ) return;
	
	if (state != POWERUPITEM_STATE_IDLE) CheckAndChangeState();

	
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

		if (isSuperLeaf)
		{
			SetLayer(SUPERLEAF_LAYER);
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			playScene->SortObjects();
		}
		break;
	case POWERUPITEM_STATE_MOVING_LEFT:
		vx = -POWERUPITEM_SPEED*1.5;
		vy = POWERUPITEM_SPEED/3;

		if (isSuperLeaf == true)
			ay = POWERUPITEM_GRAVITY * 4;// cho superleaf di chuyen cham hon
		else
			ay = POWERUPITEM_GRAVITY * 100;

		break;
	case POWERUPITEM_STATE_MOVING_RIGHT:
		vx = POWERUPITEM_SPEED*1.5;
		vy = POWERUPITEM_SPEED/3;

		if (isSuperLeaf == true)
			ay = POWERUPITEM_GRAVITY * 4; // cho superleaf di chuyen cham hon
		else
			ay = POWERUPITEM_GRAVITY * 100;

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

void CPowerUpItem::CheckAndChangeState()
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
		else if (state == POWERUPITEM_STATE_MOVING_RIGHT && x >= x_start + POWERUPITEM_SWING_WIDTH/2) //swing effect
		{
			ay = -13 * POWERUPITEM_GRAVITY;
		}
		else if (state == POWERUPITEM_STATE_MOVING_LEFT && x <= x_start) //Add a small offset to avoid the QuestionBlock covering the leaf
		{
			SetState(POWERUPITEM_STATE_MOVING_RIGHT);
		}
		else if (state == POWERUPITEM_STATE_MOVING_LEFT && x <= x_start + POWERUPITEM_SWING_WIDTH/2) //swing effect
		{
			ay = -13 * POWERUPITEM_GRAVITY;
		}
	}
	else
	{
		if (state == POWERUPITEM_STATE_EMERGING && y <= y_start - POWERUPITEM_SUPERMUSHROOM_EMERGE_HEIGHT)
		{
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			float marioX, marioY;
			(dynamic_cast<CMario*>(playScene->GetPlayer()))->GetPosition(marioX, marioY);

			if(marioX<=this->x) SetState(POWERUPITEM_STATE_MOVING_RIGHT);
			else SetState(POWERUPITEM_STATE_MOVING_LEFT);

		}
	}
	
}


