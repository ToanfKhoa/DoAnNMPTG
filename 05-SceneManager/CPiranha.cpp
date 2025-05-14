#include "CPiranha.h"



CPiranha::CPiranha(float x, float y) :CGameObject(x, y)
{
	SetState(PIRANHA_STATE_HIDE);
	isPlayerInRange = false;
	timer = 0;
	y_start = y;
}

void CPiranha::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHA_BBOX_WIDTH / 2;
	top = y - PIRANHA_BBOX_HEIGHT / 2;
	right = left + PIRANHA_BBOX_WIDTH;
	bottom = top + PIRANHA_BBOX_HEIGHT;
}

void CPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	//die
	if (this->GetState() == PIRANHA_STATE_DIE)
	{
		dieTimer += dt;
		if (dieTimer >= PIRANHA_DIE_TIME)
		{
			isDeleted = true;
			return;
		}
	}

	TrackPlayerNearby();
	UpAndDown(dt);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPiranha::Render()
{
	RenderBoundingBox();
	int aniId = ID_ANI_PIRANHA;

	//Set animation based on direction
	if (state == PIRANHA_STATE_DIE)
	{
		aniId = ID_ANI_PIRANHA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPiranha::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHA_STATE_HIDE:
		vx = 0;
		vy = 0;
		break;
	case PIRANHA_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case PIRANHA_STATE_UP:
		vy = -PIRANHA_SPEED;
		break;
	case PIRANHA_STATE_DOWN:
		vy = PIRANHA_SPEED;
		break;
	case PIRANHA_STATE_APPEAR:
		vy = 0;
		break;
	}
}

void CPiranha::UpAndDown(DWORD dt)
{
	timer += dt;

	if (isPlayerInRange == true && state == PIRANHA_STATE_HIDE && timer >= PIRANHA_HIDE_TIME)
	{
		SetState(PIRANHA_STATE_UP);
		timer = 0;
	}
	else if (state == PIRANHA_STATE_UP && y <= y_start - PIRANHA_MOVING_OFFSET)
	{
		SetState(PIRANHA_STATE_APPEAR);
		timer = 0;
	}
	else if (state == PIRANHA_STATE_APPEAR && timer >= PIRANHA_APPEAR_TIME)
	{
		SetState(PIRANHA_STATE_DOWN);
		timer = 0;
	}
	else if (state == PIRANHA_STATE_DOWN && y >= y_start)
	{
		y = y_start;
		SetState(PIRANHA_STATE_HIDE);
		timer = 0;
	}
}

void CPiranha::TrackPlayerNearby()
{
	float player_x, player_y;
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	playScene->GetPlayer()->GetPosition(player_x, player_y);

	float dx = player_x - x;
	float dy = player_y - y;

	if ((abs(player_x - this->x) <= PIRANHA_FIRE_DISTANCE_MIN + MARIO_BIG_BBOX_WIDTH / 2) || (abs(player_x - this->x) >= PIRANHA_FIRE_DISTANCE_MAX))
	{
		isPlayerInRange = false;
	}
	else
	{
		isPlayerInRange = true;
	}
}

