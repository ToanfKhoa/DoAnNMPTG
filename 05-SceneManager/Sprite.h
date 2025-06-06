#pragma once

#include "Texture.h"
#define PARALLAX_FACTOR 0.5f

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);

	void Draw(float x, float y);
	void DrawWithParallax(float x, float y, int layer);
	void DrawOnScreen(float x, float y);
};

typedef CSprite* LPSPRITE;