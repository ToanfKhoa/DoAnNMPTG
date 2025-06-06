#include "CSpawnBox.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "CKoopa.h"
#include "CParaKoopa.h"
#include "PlayScene.h"

CSpawnBox::CSpawnBox(float x, float y, int BBOX_WIDTH, int BBOX_HEIGHT, float spawnObjectX, float spawnObjectY, int spawnObjectType)
{
	isActivated = false;
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

void CSpawnBox::Spawn()
{
	if (isActivated) return;

	CGameObject* obj = NULL;

	switch (spawnObjectType)
	{
		case 0: obj = new CGoomba(spawnObjectX, spawnObjectY); break;
		case 1: obj = new CParaGoomba(spawnObjectX, spawnObjectY); break;
		case 2: obj = new CKoopa(spawnObjectX, spawnObjectY, 1); break;
		case 3: obj = new CParaKoopa(spawnObjectX, spawnObjectY, 1); break;
		case 4: obj = new CKoopa(spawnObjectX, spawnObjectY, 0); break;
	}

	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != NULL)
	{
		playScene->AddObject(obj);
	}
}
