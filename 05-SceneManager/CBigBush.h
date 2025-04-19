#pragma once
#include "GameObject.h"
class CBigBush : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdTopLeft, spriteIdTopRight, spriteIdLeft, spriteIdRight;

public:
	CBigBush(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_left, int sprite_id_right, int sprite_id_topleft, int sprite_id_topright) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdLeft = sprite_id_left;
		this->spriteIdRight = sprite_id_right;
		this->spriteIdTopLeft = sprite_id_topleft;
		this->spriteIdTopRight = sprite_id_topright;
	}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

