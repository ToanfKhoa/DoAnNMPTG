#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BULLET_SPEED 0.1f
#define ID_ANI_BULLETVENUS 5300

#define	BULLETVENUS_WIDTH 10
#define BULLETVENUS_BBOX_WIDTH 10
#define BULLETVENUS_BBOX_HEIGHT 10

class CBulletVenus : public CGameObject {
public:
	CBulletVenus(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	int IsBlocking() { return 0; }
	void Fire(float direction_x, float direction_y);
	void SetPostion(float x, float y) { this->x = x; this->y = y; }
};

typedef CBulletVenus* LPBULLETVENUS;