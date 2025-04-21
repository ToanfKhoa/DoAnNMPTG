#pragma once
#include "GameObject.h"
class CSensorBox :public CGameObject
{
protected:
	int bboxWidth;
	int bboxHeight;
	BOOLEAN isOnPlatform;

public:
	CSensorBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT);
	void Render() { RenderBoundingBox(); }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }

	boolean getIsOnPlatform() { return isOnPlatform; };
};

