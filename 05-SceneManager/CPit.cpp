#include "CPit.h"
#include "Mario.h"

CPit::CPit(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT)
{
	this->x = x;
	this->y = y;
	this->bboxWidth = BBOX_WIDTH;
	this->bboxHeight = BBOX_HEIGHT;
}

void CPit::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}
