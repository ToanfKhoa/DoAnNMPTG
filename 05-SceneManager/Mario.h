#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "CMarioHitBox.h"
#include "PlayScene.h"
#include "Game.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.09f
#define MARIO_RUNNING_SPEED		0.12f
#define MARIO_RUNNING_SPEED_RENDER 2.0f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.2f
#define MARIO_JUMP_RUN_SPEED_Y	0.25f

#define MARIO_FRICTION 0.95 //Remaining of vx each frame when applying friction 
#define MARIO_MIN_SPEED 0.01 //The minimum speed, when speed smaller this, it becomes 0

#define MARIO_GRAVITY			0.001f
#define MARIO_ON_WOODBAR_GRAVITY			0.05f

#define MARIO_JUMP_DEFLECT_SPEED  0.3f

#define MARIO_TELEPORT_SPEED	0.01f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_AFTER_WAGGING   302
#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICK			700

#define MARIO_STATE_TELEPORT		800

#define MARIO_STATE_FINISH			900
#define MARIO_STATE_FINISH_RUN		901

#pragma region ANIMATION_ID

// BIG MARIO
#define ID_ANI_MARIO_BIG_IDLE_RIGHT 400
#define ID_ANI_MARIO_BIG_IDLE_LEFT 401

#define ID_ANI_MARIO_BIG_HOLDING_IDLE_RIGHT 410
#define ID_ANI_MARIO_BIG_HOLDING_IDLE_LEFT 411

#define ID_ANI_MARIO_BIG_WALKING_RIGHT 500
#define ID_ANI_MARIO_BIG_WALKING_LEFT 501

#define ID_ANI_MARIO_BIG_HOLDING_WALKING_RIGHT 510
#define ID_ANI_MARIO_BIG_HOLDING_WALKING_LEFT 511

#define ID_ANI_MARIO_BIG_RUNNING_RIGHT 600
#define ID_ANI_MARIO_BIG_RUNNING_LEFT 601

#define ID_ANI_MARIO_BIG_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_BIG_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_BIG_HOLDING_JUMP_RIGHT 710
#define ID_ANI_MARIO_BIG_HOLDING_JUMP_LEFT 711

#define ID_ANI_MARIO_BIG_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_BIG_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_BIG_SIT_RIGHT 900
#define ID_ANI_MARIO_BIG_SIT_LEFT 901

#define ID_ANI_MARIO_BIG_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BIG_BRACE_LEFT 1001

#define ID_ANI_MARIO_BIG_KICK_RIGHT	1010
#define ID_ANI_MARIO_BIG_KICK_LEFT	1011

#define ID_ANI_MARIO_BIG_TRANSFORM_RIGHT 1020
#define ID_ANI_MARIO_BIG_TRANSFORM_LEFT 1021

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_BIG_TELEPORT 1030
// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_HOLDING_IDLE_RIGHT 1110
#define ID_ANI_MARIO_SMALL_HOLDING_IDLE_LEFT 1112

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_HOLDING_WALKING_RIGHT 1210
#define ID_ANI_MARIO_SMALL_HOLDING_WALKING_LEFT 1211

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_HOLDING_JUMP_RIGHT 1510
#define ID_ANI_MARIO_SMALL_HOLDING_JUMP_LEFT 1511

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT	1610
#define ID_ANI_MARIO_SMALL_KICK_LEFT	1611

#define ID_ANI_MARIO_SMALL_TELEPORT	1620

//RACOON MARIO
#define ID_ANI_MARIO_RACOON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACOON_IDLE_LEFT 1701

#define ID_ANI_MARIO_RACOON_HOLDING_IDLE_RIGHT 1710
#define ID_ANI_MARIO_RACOON_HOLDING_IDLE_LEFT 1711

#define ID_ANI_MARIO_RACOON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACOON_WALKING_LEFT 1801

#define ID_ANI_MARIO_RACOON_HOLDING_WALKING_RIGHT 1810
#define ID_ANI_MARIO_RACOON_HOLDING_WALKING_LEFT 1811

#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACOON_RUNNING_LEFT 1901

#define ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT 2000
#define ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT 2001

#define ID_ANI_MARIO_RACOON_FALL_RIGHT 2002
#define ID_ANI_MARIO_RACOON_FALL_LEFT 2003
#define ID_ANI_MARIO_RACOON_FALL_WAG_RIGHT 2004
#define ID_ANI_MARIO_RACOON_FALL_WAG_LEFT 2005

#define ID_ANI_MARIO_RACOON_HOLDING_JUMP_RIGHT 2010
#define ID_ANI_MARIO_RACOON_HOLDING_JUMP_LEFT 2011

#define ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT 2100
#define ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT 2101
#define ID_ANI_MARIO_RACOON_JUMP_WAG_RIGHT 2102
#define ID_ANI_MARIO_RACOON_JUMP_WAG_LEFT 2103

#define ID_ANI_MARIO_RACOON_SIT_RIGHT 2200
#define ID_ANI_MARIO_RACOON_SIT_LEFT 2201

#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 2300
#define ID_ANI_MARIO_RACOON_BRACE_LEFT 2301

#define ID_ANI_MARIO_RACOON_KICK_RIGHT	2310
#define ID_ANI_MARIO_RACOON_KICK_LEFT	2311

#define ID_ANI_MARIO_RACOON_TRANSFORM	2320

#define ID_ANI_MARIO_RACOON_ATTACK_RIGHT 2321
#define ID_ANI_MARIO_RACOON_ATTACK_LEFT 2322

#define ID_ANI_MARIO_RACOON_TELEPORT 2330

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  12
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_RACOON_BBOX_WIDTH  12
#define MARIO_RACOON_BBOX_HEIGHT 24
#define MARIO_RACOON_SITTING_BBOX_WIDTH  14
#define MARIO_RACOON_SITTING_BBOX_HEIGHT 16
#define MARIO_HIT_BOX_WIDTH  26
#define MARIO_HIT_BOX_HEIGHT 10

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  10
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICK_TIME 300
#define MARIO_JUMP_TIME 400
#define MARIO_WAG_TIME 300
#define MARIO_FLY_TIME 6000
#define MARIO_ATTACK_TIME 300
#define MARIO_MAX_RUN_POWER 2000.0f //Max power = time to run
#define MARIO_TELEPORT_TIME 4000
#define GAME_OVER_TIME 2000 //Time to restart scene

#define MARIO_MIN_COMBO_SCORE 100
#define MARIO_MAX_COMBO_SCORE 8000
#define MARIO_COMBO_TIME 1000

#define POP_UP_OFFSET 16
typedef CMarioHitBox* LPHITBOX;
class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	LPHITBOX hitBox;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coins; 
	float playTime;
	int points;
	int lives;
	int comboScore;
	vector<int> cards; //0 = nothing, 1 = supermushroom, 2 = flower , 3 = star

	DWORD kickTimer;
	BOOLEAN isKicking;

	DWORD jumpTimer;
	BOOLEAN isJumping;

	DWORD wagTimer;
	BOOLEAN isWagging;
	BOOLEAN isWaggingAnimation;

	BOOLEAN isTransforming;

	LPGAMEOBJECT holdingObject;
	BOOLEAN ableToHold;

	DWORD flyTimer;
	BOOLEAN ableToFly;

	DWORD attackTimer;
	BOOLEAN isAttacking;

	DWORD teleportTimer;
	BOOLEAN isTeleporting;

	DWORD comboTimer;
	BOOLEAN isCombo;

	BOOLEAN isPushed;

	DWORD gameOverTimer;
	BOOLEAN isGameOver;
	BOOLEAN isRestarted;

	int readyTeleport; //1 = mario will move down, -1 = mario will move up

	float runPower;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
	void OnCollisionWithBulletVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithParaKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPit(LPCOLLISIONEVENT e);
	void OnCollisionWithSpawnBox(LPCOLLISIONEVENT e);
	void OnCollisionWithPSwitch(LPCOLLISIONEVENT e);
	void OnCollisionWithWoodBar(LPCOLLISIONEVENT e);
	void OnCollisionWithBoomerangBros(LPCOLLISIONEVENT e);

	void OnOverlapWithPowerUpItem(LPCOLLISIONEVENT e);
	void OnOverlapWithCoin(LPCOLLISIONEVENT e);
	void OnOverlapWithExtraLifeMushroom(LPCOLLISIONEVENT e);
	void OnOverlapWithPipePortal(LPCOLLISIONEVENT e);
	void OnOverlapWithBoomerang(LPCOLLISIONEVENT e);
	void OnOverlapWithItemRandom(LPCOLLISIONEVENT e);
	void OnOverlapWithWoodBar(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

public:
	CMario(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}
	
	int IsOverlappable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnOverlapWith(LPCOLLISIONEVENT e);

	int GetLevel() { return level; }
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void GetDamaged();

	void SetAbleToHold(BOOLEAN b) { this->ableToHold = b; };
	void Throw();

	void Setnx(int nx) { this->nx = nx; };

	void Attack();

	bool IsFullRunPower() { return runPower == MARIO_MAX_RUN_POWER; }

	int GetCoins() { return coins; };
	void SetCoins(int c) { coins = c; };
	int GetPlayTime() { return playTime; };
	int GetPoints() { return points; };
	int GetLives() { return lives; };
	void SetLives(int l) { lives = l; }
	int SetPoints(int p) { return lives; }
	void AddLives(int l) { lives += l; }
	vector<int> GetCards() { return cards; };
	void AddPoints(int p, LPGAMEOBJECT desObj);
	void AddComboPoints(LPGAMEOBJECT desObj);
	void AddCoins(int c) { coins += c; };

	float GetRunPower() { return runPower; };

	void SetReadyTeleport(int b) { this->readyTeleport = b; };

	void AddCard(int card) 
	{ 
		DebugOut(L"add card");
		if (card < 0 && card>3) return;
		if (cards.size() < 3)
			cards.push_back(card);
		else
			DebugOut(L"full card");
	};

	BOOLEAN GetIsRestarted() { return isRestarted; }
	void SetCards(vector<int> c) 
	{ 
		cards.clear();
		for (int i = 0; i < c.size(); i++)
			cards.push_back(c[i]);
	};
};