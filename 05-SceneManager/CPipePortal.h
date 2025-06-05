#pragma once
#include "GameObject.h"

#define BBOX_WIDTH	4
#define BBOX_HEIGHT	20

class CPipePortal : public CGameObject
{
protected:
	float des_x, des_y;	// target position to switch to 
	int isReversed;
public:
	CPipePortal(float x, float y, float des_x, float des_y, int isReverse);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox(void);

	float GetDesX() { return des_x; }
	float GetDesY() { return des_y; }
	int IsBlocking() { return 0; }
	int getIsReversed () { return isReversed; }
};

