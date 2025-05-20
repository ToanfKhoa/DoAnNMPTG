#pragma once
#include "GameObject.h"

#define BBOX_WIDTH	20
#define BBOX_HEIGHT	20
class CPipePortal : public CGameObject
{
protected:
	float des_x, des_y;	// target position to switch to 

public:
	CPipePortal(float x, float y, float des_x, float des_y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox(void);

	float GetDesX() { return des_x; }
	float GetDesY() { return des_y; }
	int IsBlocking() { return 0; }
};

