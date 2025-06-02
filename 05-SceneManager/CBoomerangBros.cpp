#include "CBoomerang.h"
#include "CBoomerangBros.h"
#include "Game.h"
#include "Mario.h"

CBoomerangBros::CBoomerangBros(float x, float y) :CGameObject(x, y)
{
	this->ay = BOOMERANG_BROS_GRAVITY;
	vx = -BOOMERANG_BROS_WALKING_SPEED; //Default moving to left

	x_start = x;
	direction_x = -1; // Default direction is left

	jumpTimer = 0;
	attackTimer = ATTACK_DURATION;
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
	//x += vx * dt;
	y += vy * dt;
};

void CBoomerangBros::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}
}

void CBoomerangBros::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	float player_x, player_y;
	playScene->GetPlayer()->GetPosition(player_x, player_y);

	//Set direction
	if(player_x > x)
	{
		direction_x = 1; // Player is to the right
	}
	else
	{
		direction_x = -1; // Player is to the left
	}

	//Moving 
	if(x > x_start + MOVEMENT_OFFSET_X)
	{
		vx = -BOOMERANG_BROS_WALKING_SPEED;
	}
	else if(x < x_start - MOVEMENT_OFFSET_X)
	{
		vx = BOOMERANG_BROS_WALKING_SPEED;
	}

	//Jump
	if (jumpTimer >= JUMP_DURATION)
	{
		jumpTimer = 0;
		vy = -BOOMERANG_BROS_JUMP_SPEED; // Reset jump timer and apply jump speed
	}
	else
		jumpTimer += dt;

	//attack
	if (attackTimer >= ATTACK_DURATION && state != BOOMERANG_BROS_STATE_BOUNCE_DEATH)
	{
		if (attackTimer >= (ATTACK_DURATION + HOLDING_TIME * 3))
		{
			SetState(BOOMERANG_BROS_STATE_BOOMERANG_HOLDING);
			if (attackTimer >= (ATTACK_DURATION + HOLDING_TIME * 4))
			{
				SetState(BOOMERANG_BROS_STATE_WALKING); // Reset to walking state after full cycle
				CBoomerang* boomerang = new CBoomerang(x, y, direction_x);
				CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
				playScene->AddObject(boomerang);
				attackTimer = 0;
			}
		}
		else if(attackTimer >= (ATTACK_DURATION + HOLDING_TIME) && attackTimer < (ATTACK_DURATION + HOLDING_TIME * 2))
		{
			SetState(BOOMERANG_BROS_STATE_WALKING); // Switch back to walking state after holding duration
			CBoomerang* boomerang = new CBoomerang(x, y, direction_x);
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			playScene->AddObject(boomerang);
			attackTimer = ATTACK_DURATION + HOLDING_TIME * 2;
		}
		else if (attackTimer >= ATTACK_DURATION && attackTimer < ATTACK_DURATION + HOLDING_TIME)
		{
			SetState(BOOMERANG_BROS_STATE_BOOMERANG_HOLDING); // Switch to holding state after attack duration
		}
	}
	attackTimer += dt;

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
			aniId = ID_ANI_BOOMERANG_BROS_HOLDING_RIGHT; // Holding boomerang while walking right
		else
			aniId = ID_ANI_BOOMERANG_BROS_HOLDING_LEFT; // Holding boomerang while walking left
	}
	else
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
	if(this->state == BOOMERANG_BROS_STATE_BOUNCE_DEATH)
	{
		return;
	}

	switch (state)
	{
	case BOOMERANG_BROS_STATE_WALKING:
		break;
	case BOOMERANG_BROS_STATE_BOOMERANG_HOLDING:
		break;
	case BOOMERANG_BROS_STATE_BOUNCE_DEATH:
		vy = -BOOMERANG_BROS_BOUNCE_SPEED;
		break;
	}
	CGameObject::SetState(state);
}

void CBoomerangBros::OnOverlapWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBoomerang*>(e->obj))
	{
		OnOverlapWithBoomerang(e);
	}
}

void CBoomerangBros::OnOverlapWithBoomerang(LPCOLLISIONEVENT e)
{
	CBoomerang* boomerang = dynamic_cast<CBoomerang*>(e->obj);
	if (boomerang->GetDirection() == 0)
		boomerang->Delete();
}
