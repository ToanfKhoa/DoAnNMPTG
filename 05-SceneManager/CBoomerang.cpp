#include "CBoomerang.h"
#include "debug.h"

CBoomerang::CBoomerang(float x, float y, int direction_x) : CGameObject(x, y)
{
	ay = BOOMERANG_GRAVITY;
	ax = (direction_x < 0) ? -BOOMERANG_ACCELERATION_X : BOOMERANG_ACCELERATION_X; // Set horizontal speed based on direction
	vx = (direction_x < 0) ? -BOOMERANG_SPEED_X : BOOMERANG_SPEED_X;
	vy = -BOOMERANG_SPEED_Y;

	this->direction_x = direction_x;
	timer = 0;
}

void CBoomerang::Render()
{
	//RenderBoundingBox();
	if(direction_x < 0)
		CAnimations::GetInstance()->Get(ID_ANI_BOOMERANG_LEFT)->Render(x, y);
	else 
		CAnimations::GetInstance()->Get(ID_ANI_BOOMERANG_RIGHT)->Render(x, y);
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	x += vx * dt;
	y += vy * dt;

	timer += dt;
	if (direction_x != 0 && timer >= FLY_TIME)
	{
		ax = -ax * 10; // Reverse the horizontal acceleration to make it return, ax should be bigger than before to ensure it returns quickly
		direction_x = 0; //Use direction_x to mark that boomerang has returned
		ay = 0;
	}
	DebugOut(L"Boomerang::Update - x: %f, y: %f, vx: %f, vy: %f\n", x, y, vx, vy);
}

void CBoomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOOMERANG_BBOX_WIDTH / 2;
	t = y - BOOMERANG_BBOX_HEIGHT / 2;
	r = l + BOOMERANG_BBOX_WIDTH;
	b = t + BOOMERANG_BBOX_HEIGHT;
}