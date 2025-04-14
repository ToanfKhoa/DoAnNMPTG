#pragma once
#include "GameObject.h"

#define ID_ANI_QUESTIONBLOCK 12000
#define ID_ANI_QUESTIONBLOCK_USED 12001

#define QUESTIONBLOCK_WIDTH 16
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16

#define QUESTIONBLOCK_BOUNCING_SPEED 16
#define QUESTIONBLOCK_BOUNCE_TIME 300


#define QUESTIONBLOCK_STATE_IDLE 0
#define QUESTIONBLOCK_STATE_BOUNCING_UP 100
#define QUESTIONBLOCK_STATE_BOUNCING_DOWN 200
#define QUESTIONBLOCK_STATE_USED 300

class CQuestionBlock :public CGameObject
{
protected:
	ULONGLONG bounce_start;

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void OnNoCollision(DWORD dt);

	void Bouncing();

public:
	CQuestionBlock(float x, float y) : CGameObject(x, y) { state = QUESTIONBLOCK_STATE_IDLE; }
	void SetState(int state);
};

