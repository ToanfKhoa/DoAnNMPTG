#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
//#include "Koopas.h"

#define CAMERA_SPEED 0.04f

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;

	bool isTimeStopped = false;
	ULONGLONG timeStopStart = 0;
	bool isCameraFollowingY = true;
	bool isUnderGround = false;
	float camera_min_x = 0.0f; 
	float camera_min_y = 0.0f;
	bool isCameraAutoMoving = false;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	vector<LPGAMEOBJECT> GetObjects() { return objects; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	void AddObject(LPGAMEOBJECT obj) 
	{ 
		objects.push_back(obj);
		std::sort(objects.begin(), objects.end(), [](CGameObject* a, CGameObject* b) {
			return a->GetLayer() < b->GetLayer();
			});
	}

	void StartTimeStop();
	void UpdateCameraPosition();
	void CameraMoving(DWORD dt);
	bool GetIsUnderGround() { return isUnderGround; }
	void SetIsUnderGround(bool isUnderGround) { this->isUnderGround = isUnderGround; }
	void SetCameraMinX(float x) { camera_min_x = x; }
	void SetCameraMinY(float y) { camera_min_y = y; }
	void SetCameraAutoMoving(bool isAutoMoving) { isCameraAutoMoving = isAutoMoving; }
	bool GetIsCameraAutoMoving() { return isCameraAutoMoving; }
};

typedef CPlayScene* LPPLAYSCENE;

