#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define SPRITE_0 120010
#define SPRITE_1 120011
#define SPRITE_2 120012
#define SPRITE_3 120013
#define SPRITE_4 120014
#define SPRITE_5 120015
#define SPRITE_6 120016
#define SPRITE_7 120017
#define SPRITE_8 120018
#define SPRITE_9 120019

#define SPRITE_0_POP_UP 120022
#define SPRITE_1_POP_UP 120023
#define SPRITE_2_POP_UP 120024
#define SPRITE_4_POP_UP 120025
#define SPRITE_8_POP_UP 120026

#define SPRITE_LEVEL_UP_POP_UP 120030

class CDigit : public CGameObject
{
protected:
	int value;
	bool isOnScreen;
public:
	CDigit(float x, float y):CGameObject(x, y){
		this->value = 0;
		isOnScreen = true;
		this->layer = DIGIT_LAYER;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void Render();
	void SetValue(int value) { this->value = value; }
	void SetIsOnScreen(bool b) { isOnScreen = b; }
	int GetValue() { return value; }
};

