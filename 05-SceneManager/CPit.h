#pragma once
#include "GameObject.h"
class CPit :public CGameObject
{
protected:
	int bboxWidth;
	int bboxHeight;

public:
	CPit(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT);
	void Render() { RenderBoundingBox(); }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
};

