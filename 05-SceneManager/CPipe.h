#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

class CPipe : public CGameObject
{
protected:
	int length;		//Unit: cell
	float cellWidth;
	float cellHeight;
	int spriteIdMiddle, spriteIdEnd;

public:
	CPipe(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		this->layer = PIPE_LAYER; 
	}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetCellWidth() { return this->cellWidth; }
	int IsDirectionColliable(float nx, float ny);

};

