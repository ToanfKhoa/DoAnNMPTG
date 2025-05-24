#include "CParaKoopa.h"
#include "debug.h"
#include "PlayScene.h"

void CParaKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isKoopa)
	{
		CKoopa::GetBoundingBox(left, top, right, bottom);
		return;
	}

	left = x - KOOPA_BBOX_WIDTH / 2;
	top = y - KOOPA_BBOX_HEIGHT / 2;
	right = left + KOOPA_BBOX_WIDTH;
	bottom = top + KOOPA_BBOX_HEIGHT;
}

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isKoopa)
	{
		CKoopa::Update(dt, coObjects);
		return;
	}
	DebugOut(L"parakoopa update, state: %d\n", state);

	//Fly up and down
	if (state == PARAKOOPA_STATE_FLY_UP_DOWN)
	{
		if (y > y_start + FLY_UP_DOWN_OFFSET)
			vy = -PARAKOOPA_WALKING_SPEED;
		
		if(y < y_start - FLY_UP_DOWN_OFFSET)
			vy = PARAKOOPA_WALKING_SPEED;
	}

	vy += ay * dt;

	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParaKoopa::Render()
{
	//RenderBoundingBox();
	if (isKoopa)
	{
		CKoopa::Render();
		return;
	}

	int aniId = ID_ANI_GREEN_PARAKOOPA_WALKING_LEFT;
	if (isGreen)
	{
		if (state == PARAKOOPA_STATE_WALKING_RIGHT)
			aniId = ID_ANI_GREEN_PARAKOOPA_WALKING_RIGHT;
	}
	else
		aniId = ID_ANI_RED_PARAKOOPA_WALKING_LEFT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CParaKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (isKoopa)
	{
		DebugOut(L"parakoopa collision with, state: %d\n", state);
		CKoopa::OnCollisionWith(e);

		return;
	}

	if (!e->obj->IsBlocking()) return;


	if (e->ny != 0) //bounce
	{
		if(e->ny>0) vy = -PARAKOOPA_BOUNCE_SPEED;
		else
		vy = PARAKOOPA_BOUNCE_SPEED;
	}
	else if (e->nx != 0)
	{
		if (state == PARAKOOPA_STATE_WALKING_LEFT) SetState(PARAKOOPA_STATE_WALKING_RIGHT);
		else if (state == PARAKOOPA_STATE_WALKING_RIGHT) SetState(PARAKOOPA_STATE_WALKING_LEFT);
	}
}

CParaKoopa::CParaKoopa(float x, float y, boolean isGreen): CKoopa(x,y,isGreen)
{
	this->ay = PARAKOOPA_GRAVITY;
	this->vx = PARAKOOPA_WALKING_SPEED;

	this->isKoopa = false;

	y_start = y;

	if (isGreen)
		SetState(PARAKOOPA_STATE_WALKING_LEFT);
	else
	{
		SetState(PARAKOOPA_STATE_FLY_UP_DOWN);
		vy = PARAKOOPA_WALKING_SPEED;
	}

}

void CParaKoopa::SetState(int nextState)
{
	if (isKoopa)
	{
		CKoopa::SetState(nextState);
		return;
	}

	switch (nextState)
	{
	case PARAKOOPA_STATE_WALKING_LEFT:
		vx = -PARAKOOPA_WALKING_SPEED;
		isFlipped = false; //koopa wakes up and returns to normal
		break;

	case PARAKOOPA_STATE_WALKING_RIGHT:
		vx = PARAKOOPA_WALKING_SPEED;
		isFlipped = false; //koopa wakes up and returns to normal
		break;

	case PARAKOOPA_STATE_FLY_UP_DOWN:
		vx = 0;
		ay = 0;
		break;
	}
	CGameObject::SetState(nextState); //need to update state later to check current state
}

void CParaKoopa::TurnIntoKoopa()
{
	isKoopa = true;

	//koopa constructor
	this->x = x;
	this->y = y;
	this->isGreen = isGreen;
	ay = KOOPA_GRAVITY;
	isFlipped = false;

	if (isGreen == 0)
	{
		sensorBox = new CSensorBox(x, y, KOOPA_BBOX_WIDTH / 4, KOOPA_BBOX_HEIGHT / 4);

		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		playScene->AddObject(sensorBox);
	}
	else
		sensorBox = NULL;

	SetState(KOOPA_STATE_WALKING_LEFT);
}

