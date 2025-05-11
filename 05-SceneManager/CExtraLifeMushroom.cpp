#include "CExtraLifeMushroom.h"
#include "PlayScene.h"

CExtraLifeMushroom::CExtraLifeMushroom(float x, float y) :CGameObject(x, y)
{
	this->ay = EXTRALIFEMUSHROOM_GRAVITY;
	this->y_start = y;
	SetState(EXTRALIFEMUSHROOM_STATE_IDLE);
}
void CExtraLifeMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EXTRALIFEMUSHROOM_STATE_IDLE:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case EXTRALIFEMUSHROOM_STATE_EMERGING:
		vx = 0;
		vy = -EXTRALIFEMUSHROOM_SPEED;
		ay = -EXTRALIFEMUSHROOM_GRAVITY;
		break;
	case EXTRALIFEMUSHROOM_STATE_MOVING_LEFT:
		vx = -EXTRALIFEMUSHROOM_SPEED * 1.5;
		vy = EXTRALIFEMUSHROOM_SPEED;
		ay = EXTRALIFEMUSHROOM_GRAVITY;

		break;
	case EXTRALIFEMUSHROOM_STATE_MOVING_RIGHT:
		vx = EXTRALIFEMUSHROOM_SPEED * 1.5;
		vy = EXTRALIFEMUSHROOM_SPEED;
		ay = EXTRALIFEMUSHROOM_GRAVITY;
		break;
	case EXTRALIFEMUSHROOM_STATE_EATEN:
		vx = 0;
		vy = 0;
		ay = 0;
		isDeleted = true;
		break;
	}
}
void CExtraLifeMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - EXTRALIFEMUSHROOM_BBOX_WIDTH / 2;
	top = y - EXTRALIFEMUSHROOM_BBOX_HEIGHT / 2;
	right = left + EXTRALIFEMUSHROOM_BBOX_WIDTH;
	bottom = top + EXTRALIFEMUSHROOM_BBOX_HEIGHT;
}

void CExtraLifeMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (state == EXTRALIFEMUSHROOM_STATE_EATEN) return;

	if (state != EXTRALIFEMUSHROOM_STATE_IDLE) CheckAndChangeState();

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CExtraLifeMushroom::Render()
{
	if (state == EXTRALIFEMUSHROOM_STATE_IDLE) return;
	CAnimations* animation = CAnimations::GetInstance();
	animation->Get(ID_ANI_EXTRALIFEMUSHROOM)->Render(x, y);
}

void CExtraLifeMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CExtraLifeMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CExtraLifeMushroom::CheckAndChangeState()
{
	if (state == EXTRALIFEMUSHROOM_STATE_EMERGING && y <= y_start - EXTRALIFEMUSHROOM_EMERGE_HEIGHT)
	{
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		float marioX, marioY;
		(dynamic_cast<CMario*>(playScene->GetPlayer()))->GetPosition(marioX, marioY);

		if (marioX <= this->x) SetState(EXTRALIFEMUSHROOM_STATE_MOVING_RIGHT); 
		else SetState(EXTRALIFEMUSHROOM_STATE_MOVING_LEFT);

	}
}


