#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "CKoopa.h"
#include "ParaGoomba.h"
#include "CQuestionBlock.h"
#include "Brick.h"
#include "CParaKoopa.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	float marioX, marioY;
	int nx = mario->GetNx();
	mario->GetPosition(marioX, marioY);

	CGameObject* obj = NULL;

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetReadyTeleport(1);
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_UP:
		mario->SetReadyTeleport(-1);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_K:
		DebugOut(L"k\n");
		mario->SetState(MARIO_STATE_KICK);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_4:
		if (nx > 0)
			obj = new CKoopa(marioX + 32, marioY - 32, 1);
		else
			obj = new CKoopa(marioX - 32, marioY - 32, 0);

		obj->SetState(KOOPA_STATE_SHELL_IDLE);
		playScene->AddObject(obj);
		break;

	case DIK_5:

		if (nx > 0)
			obj = new CParaGoomba(marioX + 32, marioY - 32);
		else
			obj = new CParaGoomba(marioX - 32, marioY - 32);

		playScene->AddObject(obj);
		break;

	case DIK_6:

		if (nx > 0)
			obj = new CGoomba(marioX + 32, marioY - 32);
		else
			obj = new CGoomba(marioX - 32, marioY - 32);

		playScene->AddObject(obj);
		break;

	case DIK_7:

		if (nx > 0)
			obj = new CQuestionBlock(marioX + 32, marioY, 1);
		else
			obj = new CQuestionBlock(marioX - 32, marioY, 1);

		playScene->AddObject(obj);
		break;

	case DIK_8:

		if (nx > 0)
			obj = new CBrick(marioX + 32, marioY, 0);
		else
			obj = new CBrick(marioX - 32, marioY, 3);

		playScene->AddObject(obj);
		break;
	case DIK_9:
		if (nx > 0)
			obj = new CParaKoopa(marioX + 32, marioY - 32, 1);
		else
			obj = new CParaKoopa(marioX - 32, marioY - 32, 1);

		playScene->AddObject(obj);
		break;

	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		CGame::GetInstance()->ReLoad();
		break;
	case DIK_A:
		mario->SetAbleToHold(true);
		if (mario->GetLevel() == MARIO_LEVEL_RACOON)
			mario->Attack();
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->Throw();
		mario->SetAbleToHold(false);
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_DOWN)) //Stop receiving other keys input while sitting
		return; 
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);

		mario->Setnx(1);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);

		mario->Setnx(-1);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}