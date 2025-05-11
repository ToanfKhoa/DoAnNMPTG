#include "CMarioHitBox.h"
#include "CVenus.h"
#include "Goomba.h"
#include "CKoopa.h"
#include "CQuestionBlock.h"
#include "Brick.h"

CMarioHitBox::CMarioHitBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT)
{
	this->x = x;
	this->y = y;
	this->bboxWidth = BBOX_WIDTH;
	this->bboxHeight = BBOX_HEIGHT;
	isActive = false;
}

void CMarioHitBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isActive)
		return;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioHitBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}


