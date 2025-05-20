#pragma once
#include "GameObject.h"

#define ID_ANI_PSWITCH_IDLE 
#define ID_ANI_PSWITCH_USED 

#define PSWITCH_BBOX_WIDTH 16
#define PSWITCH_BBOX_HEIGHT 16

#define PSWITCH_EFFECT_RANGE_X	80
#define PSWITCH_EFFECT_RANGE_Y	80
#define PSWITCH_EFFECT_TIME 10000	

#define PSWITCH_STATE_IDLE 0
#define PSWITCH_STATE_EFFECT 100
#define PSWITCH_STATE_USED 200


class CPSwitch :public CGameObject
{
protected:
	ULONGLONG timeEffectStart = 0;

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

public:
	CPSwitch(float x, float y) : CGameObject(x, y) {};
	void SetState(int state);
	void Switch();
};

