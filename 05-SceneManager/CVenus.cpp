#include "CVenus.h"
#include "debug.h"
#include "CBulletVenus.h"
#include "PlayScene.h"
#include "Game.h"

CVenus::CVenus(float x, float y) :CGameObject(x, y)
{
	SetState(VENUS_STATE_HIDE);
	timer = 0;
	this->bullet = new CBulletVenus(x, y);
	
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != NULL)
	{
		playScene->AddObject(bullet);
	}
	else
	{
		DebugOut(L"[ERROR] CVenus::CVenus: Scene is NULL\n");
	}
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
		Fire();
		vy = 0;
		break;
	}
}

void CVenus::UpAndDown(DWORD dt)
{
	timer += dt;

	if(state == VENUS_STATE_HIDE && timer >= VENUS_HIDE_TIME)
	{
		SetState(VENUS_STATE_UP);
		timer = 0;
	}
	else if (state == VENUS_STATE_UP && timer >= VENUS_MOVE_TIME)
	{
		SetState(VENUS_STATE_FIRE);
		timer = 0;
	}
	else if (state == VENUS_STATE_FIRE && timer >= VENUS_APPEAR_TIME)
	{
		SetState(VENUS_STATE_DOWN);
		timer = 0;
	}
	else if (state == VENUS_STATE_DOWN && timer >= VENUS_MOVE_TIME)
	{
		SetState(VENUS_STATE_HIDE);
		timer = 0;
	}
}

void CVenus::Fire()
{
	this->bullet->SetPosition(x, y);
	float mario_x, mario_y;

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	float player_x, player_y;
	playScene->GetPlayer()->GetPosition(player_x, player_y);
	this->bullet->Fire(player_x - this->x, player_y - this->y);
}
