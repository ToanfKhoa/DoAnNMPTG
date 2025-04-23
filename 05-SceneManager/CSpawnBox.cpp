#include "CSpawnBox.h"

CSpawnBox::CSpawnBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT, float spawnObjectX, float spawnObjectY, int spawnObjectType)
{
	this->x = x;
	this->y = y;
	this->bboxWidth = BBOX_WIDTH;
	this->bboxHeight = BBOX_HEIGHT;
	this->spawnObjectX = spawnObjectX;
	this->spawnObjectY = spawnObjectY;
	this->spawnObjectType = spawnObjectType;
}

void CSpawnBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}
