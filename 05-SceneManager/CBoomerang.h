#pragma once
#include "GameObject.h"

#define ID_ANI_BOOMERANG_LEFT 20000
#define ID_ANI_BOOMERANG_RIGHT 20001

#define BOOMERANG_GRAVITY 0.0002f
#define BOOMERANG_ACCELERATION_X 0.00005f	
#define BOOMERANG_SPEED_X 0.1f
#define BOOMERANG_SPEED_Y 0.12f

#define BOOMERANG_BBOX_WIDTH 16
#define BOOMERANG_BBOX_HEIGHT 16

#define FLY_TIME 800.0f
class CBoomerang : public CGameObject
{
protected:
	float ax, ay;
	DWORD timer;
	int direction_x; // Direction of the boomerang, 1 for right, -1 for left
public:
	CBoomerang(float x, float y, int direction_x);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

