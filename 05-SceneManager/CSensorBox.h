#pragma once
#include "GameObject.h"

#define SENSORBOX_SPEED 0.02f
#define SENSORBOX_GRAVITY 0.02f
#define SENSORBOX_NO_COLLISION_THRESHOLD 1000

class CSensorBox :public CGameObject
{
protected:
	float ay;
	int bboxWidth;
	int bboxHeight;
	BOOLEAN isOnPlatform;

public:
	CSensorBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT);
	void Render() { /*RenderBoundingBox();*/ }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }

	boolean getIsOnPlatform() { return isOnPlatform; };
	float GetY() { return y; }
};

