#include "CVenus.h"
#include "debug.h"
#include "CBulletVenus.h"
#include "CPipe.h"
#include "PlayScene.h"
#include "Game.h"


CVenus::CVenus(float x, float y) :CGameObject(x, y)
{
	SetState(VENUS_STATE_HIDE);
	isPlayerInRange = false;
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

void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	//die
	if (this->GetState() == VENUS_STATE_DIE)
	{
		isDeleted = true;
		return;
	}

	TrackPlayerNearby();
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

	if(isPlayerInRange == true && state == VENUS_STATE_HIDE && timer >= VENUS_HIDE_TIME)
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
	// Set bullet position at venus position
	this->bullet->SetPosition(x, y);

	// Get player position
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	float player_x, player_y;
	playScene->GetPlayer()->GetPosition(player_x, player_y);
	
	// Find the direction vector and convert to angle
	float dx = player_x - x;
	float dy = player_y - y;
	float angle = atan2(-dy, dx); // Value in [-π, π]

	// Turn radian to degree for clarity [0, 360°)
	float angle_deg = angle * 180.0f / 3.1416;
	if (angle_deg < 0) angle_deg += 360.0f;

	// Venus only fires 1 in 8 directions
	float fixed_angle_deg;
	if (angle_deg >= 0.0f && angle_deg < 22.5f)
		fixed_angle_deg = 22.5f; 
	else if (angle_deg >= 22.5f && angle_deg < 90.0f)
		fixed_angle_deg = 45.0f;
	else if (angle_deg >= 90.0f && angle_deg < 157.5f)
		fixed_angle_deg = 135.0f; 
	else if (angle_deg >= 157.5f && angle_deg < 180.0f)
		fixed_angle_deg = 157.5f; 
	else if (angle_deg >= 180.0f && angle_deg < 202.5f)
		fixed_angle_deg = 202.5f;
	else if (angle_deg >= 202.5f && angle_deg < 270.0f)
		fixed_angle_deg = 225.0f;
	else if (angle_deg >= 270.0f && angle_deg < 337.5f)
		fixed_angle_deg = 315.0f;
	else
		fixed_angle_deg = 337.5f; 

	// Turn back to radian
	float fixed_angle_rad = fixed_angle_deg * 3.1416 / 180.0f;
	// Use cos and sin to find x, y of direction vector
	this->bullet->Fire(cos(fixed_angle_rad), -sin(fixed_angle_rad));
}

void CVenus::TrackPlayerNearby()
{
	float player_x, player_y;
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	playScene->GetPlayer()->GetPosition(player_x, player_y);

	float dx = player_x - x;
	float dy = player_y - y;

	if (dx >= 0 && dy < 0)       // top left
		SetDirection(1, -1);
	else if (dx < 0 && dy < 0)   // top right
		SetDirection(-1, -1);
	else if (dx >= 0 && dy >= 0)   // bot left
		SetDirection(1, 1);
	else if (dx < 0 && dy >= 0)    // bot right
		SetDirection(-1, 1);

	if ((abs(player_x - this->x) <= VENUS_FIRE_DISTANCE_MIN + MARIO_BIG_BBOX_WIDTH/2) || (abs(player_x - this->x) >= VENUS_FIRE_DISTANCE_MAX))
	{
		isPlayerInRange = false;
	}
	else
	{
		isPlayerInRange = true;
	}
}
