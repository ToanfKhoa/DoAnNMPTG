#pragma once
#include "GameObject.h"
class CSensorBox :public CGameObject
{
	int bboxWidth;
	int bboxHeight;
public:
	CSensorBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT);
	void Render() { RenderBoundingBox(); }
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
};

