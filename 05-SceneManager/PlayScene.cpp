#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "ParaGoomba.h"
#include "CGround.h"
#include "CQuestionBlock.h"
#include "CVenus.h"
#include "CPowerUpItem.h"
#include "CPipe.h"
#include "CColorBlock.h"
#include "CCoinItem.h"
#include "CKoopa.h"
#include "CBigBush.h"
#include "CDecoration.h"
#include "CWoodBlock.h"
#include "CPit.h"
#include "CSpawnBox.h"
#include "CHeadsUpDisplay.h"
#include "CExtraLifeMushroom.h"
#include "CParaKoopa.h"
#include "CPSwitch.h"
#include "CPipePortal.h"
#include "CPiranha.h"
#include "SampleKeyEventHandler.h"
#include "CWoodBar.h"
#include "CBoomerangBros.h"
#include "CItemRandom.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

#define TIME_STOP_DURATION 500

#define END_OF_MAP_LEVEL_1 2524
#define END_OF_MAP_LEVEL_4 2302
#define END_OF_SKY -188

#define DEADZONE_X 16
#define DEADZONE_Y 32

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x,y); break;
	case OBJECT_TYPE_BRICK:
	{
		int item_type = atoi(tokens[3].c_str());
		obj = new CBrick(x, y, item_type); 
		break;
	}
	case OBJECT_TYPE_COIN:
	{
		int count = atoi(tokens[3].c_str());
		int x_spacing = atoi(tokens[4].c_str());
		int y_spacing = atoi(tokens[5].c_str());

		obj = new CCoin(x, y);

		for (int i = 1; i < count; i++)
		{
		    CCoin* coin = new CCoin(x + i * x_spacing, y + i * y_spacing);
			objects.push_back(coin);
		}

		break;
	}

	case OBJECT_TYPE_PARAGOOMBA: obj = new CParaGoomba(x, y); break;
	case OBJECT_TYPE_QUESTIONBLOCK:
	{
		int item_type = atoi(tokens[3].c_str());
		obj = new CQuestionBlock(x, y, item_type); 
		break;
	}
	case OBJECT_TYPE_VENUS:
	{
		BOOLEAN isGreen = atoi(tokens[3].c_str());
		obj = new CVenus(x, y, isGreen);
		break;
	}
	case OBJECT_TYPE_PIRANHA: obj = new CPiranha(x, y); break;
	case OBJECT_TYPE_POWERUPITEM: obj = new CPowerUpItem(x, y); break;
	case OBJECT_TYPE_EXTRALIFEMUSHROOM: obj = new CExtraLifeMushroom(x, y); break;
	case OBJECT_TYPE_PSWITCH: obj = new CPSwitch(x, y); break;
	case OBJECT_TYPE_ITEMRANDOM:
	{
		int nextScene_id = atoi(tokens[3].c_str());
		obj = new CItemRandom(x, y, nextScene_id); 
		break;
	}
	case OBJECT_TYPE_COINITEM: obj = new CCoinItem(x, y); break;
	case OBJECT_TYPE_KOOPA:
	{
		//0 = red koopa, 1 = green koopa
		int koopa_type = atoi(tokens[3].c_str());
		obj = new CKoopa(x, y, koopa_type); 
		break;
	}
	case OBJECT_TYPE_PARAKOOPA:
	{
		//1 = green parakoopa
		int koopa_type = atoi(tokens[3].c_str());
		obj = new CParaKoopa(x, y, koopa_type); 
		break;
	}
	case OBJECT_TYPE_BOOMERANG_BROS: obj = new CBoomerangBros(x, y); break;
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_GROUND:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CGround(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PIPE:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_middle = atoi(tokens[6].c_str());
		int sprite_end = atoi(tokens[7].c_str());

		obj = new CPipe(
			x, y,
			cell_width, cell_height, length,
			sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_COLORBLOCK:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length_x = atoi(tokens[5].c_str());
		int length_y = atoi(tokens[6].c_str());
		int sprite_id_middle = atoi(tokens[7].c_str());
		int sprite_id_topleft = atoi(tokens[8].c_str());
		int sprite_id_topright = atoi(tokens[9].c_str());
		int sprite_id_botleft = atoi(tokens[10].c_str());
		int sprite_id_botright = atoi(tokens[11].c_str());
		int sprite_id_left = atoi(tokens[12].c_str());
		int sprite_id_right = atoi(tokens[13].c_str());
		int sprite_id_top = atoi(tokens[14].c_str());
		int sprite_id_bot = atoi(tokens[15].c_str());
		int hasShadow = atoi(tokens[16].c_str());

		obj = new CColorBlock(
			x, y,
			cell_width, cell_height,
			length_x, length_y,
			sprite_id_middle,
			sprite_id_topleft, sprite_id_topright,
			sprite_id_botleft, sprite_id_botright,
			sprite_id_left, sprite_id_right,
			sprite_id_top, sprite_id_bot,
			hasShadow
		);

		break;
	}

	case OBJECT_TYPE_BIGBUSH: 
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_id_left = atoi(tokens[6].c_str());
		int sprite_id_right = atoi(tokens[7].c_str());
		int sprite_id_topleft = atoi(tokens[8].c_str());
		int sprite_id_topright = atoi(tokens[9].c_str());

		obj = new CBigBush(
			x, y,
			cell_width, cell_height, length,
			sprite_id_left, sprite_id_right,
			sprite_id_topleft, sprite_id_topright
		);
		break;
	}

	case OBJECT_TYPE_DECORATION:
	{
		int count = atoi(tokens[3].c_str());
		int x_spacing = atoi(tokens[4].c_str());
		int y_spacing = atoi(tokens[5].c_str());
		int spriteId = atoi(tokens[6].c_str());

		obj = new CDecoration(x, y, spriteId);

		for (int i = 1; i < count; i++)
		{
			CDecoration* decoration = new CDecoration(x + i * x_spacing, y + i * y_spacing, spriteId);
			objects.push_back(decoration);
		}

		break;
	}

	case OBJECT_TYPE_WOODBLOCK:
	{
		obj = new CWoodBlock(x, y);
		break;
	}

	case OBJECT_TYPE_WOODBAR:
	{
		obj = new CWoodBar(x, y);
		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atoi(tokens[3].c_str());
		float b = (float)atoi(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}

	case OBJECT_TYPE_PIPE_PORTAL:
	{
		float des_x = (float)atoi(tokens[3].c_str());
		float des_y = (float)atoi(tokens[4].c_str());
		int isReverse = (int)atoi(tokens[5].c_str());
		obj = new CPipePortal(x, y, des_x, des_y, isReverse);
		break;
	}

	case OBJECT_TYPE_PIT:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		obj = new CPit(x, y, width, height);
		break;
	}
	case OBJECT_TYPE_SPAWNBOX:
	{
		int bboxWidth = atoi(tokens[3].c_str());
		int bboxHeight = atoi(tokens[4].c_str());

		float spawnObjectX = (float)atof(tokens[5].c_str());;
		float spawnObjectY = (float)atof(tokens[6].c_str());;
		int spawnObjectType = atoi(tokens[7].c_str());;
		obj = new CSpawnBox(x, y, bboxWidth, bboxHeight, spawnObjectX, spawnObjectY, spawnObjectType);
		break;
	}
	case OBJECT_TYPE_HUD:
	{
		int spriteId = atoi(tokens[3].c_str());
		obj = new CHeadsUpDisplay(x, y, spriteId);

		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	//objects.push_back(obj);
	//add and sort layer
	AddObject(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	if (isTimeStopped) 
	{
		if (GetTickCount64() - timeStopStart >= TIME_STOP_DURATION) 
		{
			isTimeStopped = false;
		}
		else return;
	}

	CMario* player = dynamic_cast<CMario*>(GetPlayer());
	if (player != NULL)
	{
		if (player->GetIsRestarted())
		{
			CGame* game = CGame::GetInstance();
			game->ReLoad(game->GetCurrentIndexScene());
			return;
		}
	}

	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++) 
	{
		if (!dynamic_cast<CMario*>(objects[i]))
			coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	//DebugOut(L"Cameraaaaaa to %f, %f\n", cx, cy);
	// Update camera to follow mario
	if (isCameraAutoMoving)
	{	
		CameraMoving(dt);
	}
	else
	{
		UpdateCameraPosition();
	}

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::StartTimeStop()
{
	isTimeStopped = true;
	timeStopStart = GetTickCount64();
}

void CPlayScene::UpdateCameraPosition()
{
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	float centerX, centerY;
	game->GetCamPos(centerX, centerY);

	//x direction
	if (cx < centerX - DEADZONE_X || cx > centerX + DEADZONE_X)
	{
		//set cam pos with cx +- DEADZONE for smoother follow 
		if (cx < centerX - DEADZONE_X)
		{
			cx += DEADZONE_X;
		}
		else
		{
			cx -= DEADZONE_X;
		}
	}
	else cx = centerX;

	//y direction
	CMario* mario = dynamic_cast<CMario*>(player);
	if (mario->IsFullRunPower() && cy < centerY - DEADZONE_Y && isUnderGround==false)
	{
		isCameraFollowingY = true;
	};
	if (isCameraFollowingY)	cy += DEADZONE_Y;

	if (cx > end_of_map) cx = end_of_map;
	if (cx < camera_min_x) cx = camera_min_x;
	if (cy < END_OF_SKY) cy = END_OF_SKY;

	if (!isUnderGround)
	{
		if (cy >= camera_min_y || isCameraFollowingY == false)
		{
			isCameraFollowingY = false;
			cy = camera_min_y;
		}
	}
	else
	{
		cy = 832;
	}
	
	//DebugOut(L"camera cy: %f\n", cy);
	CGame::GetInstance()->SetCamPos(cx, cy);
}

void CPlayScene::CameraMoving(DWORD dt)
{
	float cx, cy;

	CGame* game = CGame::GetInstance();
	game->GetCamPos(cx, cy);

	if (cx >= 1763)
	{
		cx = 1763;
		//isCameraAutoMoving = false;
	}
	else
	{
		cx += CAMERA_SPEED * dt;
	}
	cy = 237;

	CGame::GetInstance()->SetCamPos(cx, cy);
}

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}