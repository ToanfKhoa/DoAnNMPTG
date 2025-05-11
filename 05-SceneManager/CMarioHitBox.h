#pragma once
#include "GameObject.h"

class CMarioHitBox : public CGameObject
{
protected:
	int bboxWidth;
	int bboxHeight;
	BOOLEAN isActive;
public:
	CMarioHitBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT);
	void Render() { /*RenderBoundingBox();*/ }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	void SetIsActive(BOOLEAN b) { isActive = b; }
};

