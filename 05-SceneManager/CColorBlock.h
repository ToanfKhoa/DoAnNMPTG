#pragma once
#include "GameObject.h"
class CColorBlock : public CGameObject
{
protected:
	int length_x, length_y;		//Unit: cell
	float cellWidth;
	float cellHeight;
	int spriteIdMiddle, spriteIdTopLeft, spriteIdTopRight,
		spriteIdBotLeft, spriteIdBotRight,
		spriteIdLeft, spriteIdRight,
		spriteIdTop, spriteIdBot;

public:
	CColorBlock(float x, float y,
		float cell_width, float cell_height,
		int length_x, int length_y,
		int sprite_id_middle, 
		int sprite_id_topleft, int sprite_id_topright,
		int sprite_id_botleft, int sprite_id_botright,
		int sprite_id_left, int sprite_id_right,
		int sprite_id_top, int sprite_id_bot, int color) :CGameObject(x, y)
	{
		this->length_x = length_x;
		this->length_y = length_y;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdTopLeft = sprite_id_topleft;
		this->spriteIdTopRight = sprite_id_topright;
		this->spriteIdBotLeft = sprite_id_botleft;
		this->spriteIdBotRight = sprite_id_botright;
		this->spriteIdLeft = sprite_id_left;
		this->spriteIdRight = sprite_id_right;
		this->spriteIdTop = sprite_id_top;
		this->spriteIdBot = sprite_id_bot;
	}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetCellWidth() { return this->cellWidth; }
	int IsDirectionColliable(float nx, float ny);
};

