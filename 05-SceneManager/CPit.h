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
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
};

