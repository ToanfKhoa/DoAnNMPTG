#pragma once
#include "GameObject.h"

class CSpawnBox :public CGameObject
{
protected:
	boolean isActivated;

	int bboxWidth;
	int bboxHeight;

	float spawnObjectX;
	float spawnObjectY;
	int spawnObjectType; // 0 = goomba, 1 = paragoomba, 2 = green koopa, 3 = green parakoopa

public:
	CSpawnBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT, float spawnObjectX, float spawnObjectY, int spawnObjectType);
	void Render() { /*RenderBoundingBox();*/ }
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }

	void SetIsActivated(boolean value) { isActivated = value; }
	void Spawn();
};

