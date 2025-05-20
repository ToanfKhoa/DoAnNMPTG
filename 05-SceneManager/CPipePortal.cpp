#include "CPipePortal.h"
#include "Game.h"
#include "Textures.h"

CPipePortal::CPipePortal(float x, float y, float des_x, float des_y)
{
	this->des_x = des_x;
	this->des_y = des_y;
}

void CPipePortal::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}


void CPipePortal::Render()
{
	//RenderBoundingBox();
}

void CPipePortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BBOX_WIDTH / 2;
	t = y - BBOX_HEIGHT / 2;
	r = x + BBOX_WIDTH / 2;
	b = y + BBOX_HEIGHT / 2;
}