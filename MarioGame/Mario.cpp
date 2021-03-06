#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include "Animations.h"
#include "Goomba.h"
#include "Portal.h"
#include "Box.h"
#include "KooPas.h"
#include "BackGroundCollision.h"
#include"QuestionBlock.h"
#include"Ball.h"
#include"Coin.h"
#include"Breakable_Brick.h"
#include"Flower.h"
#include "Item.h"
#include"KoopasBrick.h"
#include"WingGoomba.h"
#include"Pbell.h"
#include"HoldBrick.h"
#include"StartScence.h"
#include"Card.h"
#include"MovingBrick.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	SetState(MARIO_STATE_IDLE);
	SetHolding(0);
	CanFly = 0;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

CMario::CMario(int type, float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	this->type = type;
	SetHolding(0);
	CanFly = 0;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	int id = CGame::GetInstance()->GetCurrentScene()->GetId();

	// Simple fall down
	if (state != MARIO_STATE_FALL)
	{
		vy += MARIO_GRAVITY * dt;
	}

	else
	{
		vy += MARIO_GRAVITY_FALL / 9000.0f * dt;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE && state != MARIO_STATE_MOVE_UP && state != MARIO_STATE_MOVE_DOWN)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > 2000)

	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (GetTickCount() - swichscece_start > 2000 && swichWorldMap == 1)
	{
		CGame::GetInstance()->SwitchScene(2);
	}
	if (jump == true && doubleJump_start != 0)
	{
		if (GetTickCount() - doubleJump_start > 100)
		{
			vy = -MARIO_DOUBLE_JUMP_SPEED;
			doubleJump_start = 0;
		}
	}


	if (GetTickCount() - preIDLE_start > 250 && preIdled == 1 && id==3)
	{
		preIDLE_start = 0;
		preIdled = 0;

	}
	if (GetTickCount() - preIDLE_start > 150 && preIdled == 1 && id == 4)
	{
		preIDLE_start = 0;
		preIdled = 0;

	}

	if (maxjumping == 1)
	{
		if (GetTickCount() - time_maxjumping > 100 && GetTickCount() - time_maxjumping < 200)
		{
			vy = -0.18f;
		}
		else if (GetTickCount() - time_maxjumping >= 200)
		{
			vy = -0.24f;
			maxjumping = 0;
			time_maxjumping = 0;
		}
	}
	else
	{
		maxjumping = 0;
		time_maxjumping = 0;
	}
	if (preIdled == 1)
	{
		if (nx > 0)
			SetState(MARIO_STATE_WALKING_RIGHT);

		else if (nx < 0)
			SetState(MARIO_STATE_WALKING_LEFT);

	}

	if (GetTickCount() - spin_start > 400)
	{
		spin_start = 0;
		SetSpin(0);
	}


	// No collision occured, proceed normally
	if (GetTickCount() - kick_start > 500)
	{
		AniKick = 0;
	}



	if (FirstTimeFly == 1 && GetTickCount() - fly_start >= 5000)
	{
		CanFly = 0;
		SetState(MARIO_STATE_FALL);
	}

	if ((state == MARIO_STATE_DIE && swichWorldMap == 0) || (id == 4 && y > 300 && swichWorldMap == 0))
	{
		StartSwichScence();
		resetcam = 1;
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}

	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?


		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//mario touches ground
		if (ny != 0 && nx == 0)
		{
			FirstTimeFly = 0;
			CanFly = 0;
			vy = 0;
			if (GetJumping() == 1)
			{
				jump = 0;
				doubleJump_start = 0;
				SetCheckFall(false);
			}

			//CanFall = 0;
		}

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			float x, y;
			GetPosition(x, y);

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						goomba->GoombaDie();
						goomba->SetTickCount();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else {
						goomba->SetState(GOOMBA_STATE_DIE);
						goomba->GoombaDie();
						goomba->SetTickCount();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}

				else if (e->nx != 0 && GetSpin() == 0)
				{
					if (level == MARIO_LEVEL_BIG)
					{
						StartUntouchable();
						SetLevel(MARIO_LEVEL_SMALL);
						if (nx > 0)
							SetPosition(x - 20, y);
						else if (nx < 0)
							SetPosition(x + 20, y);
					}
					else if (level == MARIO_LEVEL_SMALL)
					{
						StartUntouchable();
						SetState(MARIO_STATE_DIE);
					}
					else
					{
						StartUntouchable();
						SetLevel(MARIO_LEVEL_BIG);
						if (nx > 0)
							SetPosition(x - 20, y);
						else if (nx < 0)
							SetPosition(x + 20, y);
					}
				}
				else if (GetSpin() == 1)
				{
					float xg, yg;
					goomba->GetPosition(xg, yg);
					goomba->SetPosition(xg, yg - 30);
					SetPosition(x, y - 5);
					goomba->SetState(GOOMBA_STATE_DIE_FALL);
					/*	goomba->GoombaDie();
						goomba->SetTickCount();*/
				}
			}
			//else if (dynamic_cast<CWingGoomba*>(e->obj)) // if e->obj is Goomba 
			//{
			//	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			//	goomba->GoombaDie();
			//}
		
			else if (dynamic_cast<CKoopas*>(e->obj)) // if e->obj is Goomba 
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

				if (e->ny < 0)
				{
					if (koopas->GetType() == KOOPAS_TYPE_WING)
					{
						koopas->SetType(KOOPAS_TYPE_GREEN);
					}
					else if (type == KOOPAS_TYPE_GREEN_WING)
					{
						koopas->SetTouch(1);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else if (koopas->GetState() != KOOPAS_STATE_SHELL && type != KOOPAS_TYPE_GREEN_WING)
					{
						koopas->SetState(KOOPAS_STATE_SHELL);
						vy = -MARIO_JUMP_DEFLECT_SPEED;


					}
					else if (koopas->GetState() == KOOPAS_STATE_SHELL)
					{
						koopas->SetState(SHELL_STATE_WALKING_LEFT);
					}

				}

				else if (nx != 0)
				{
					if (GetSpin() != 1)
					{
						if (koopas->GetState() != KOOPAS_STATE_SHELL)
						{

							if (level == MARIO_LEVEL_BIG)
							{
								StartUntouchable();
								SetLevel(MARIO_LEVEL_SMALL);
								if (nx > 0)
									SetPosition(x - 30, y);
								else if (nx < 0)
									SetPosition(x + 30, y);

							}
							else if (level == MARIO_LEVEL_SMALL)
							{
								StartUntouchable();
								SetState(MARIO_STATE_DIE);
							}
							else
							{
								StartUntouchable();
								SetLevel(MARIO_LEVEL_BIG);
								if (nx > 0)
									SetPosition(x - 20, y);
								else if (nx < 0)
									SetPosition(x + 20, y);
							}
						}
					}
					else if (GetSpin() == 1 && level == MARIO_LEVEL_TAIL)
					{
						koopas->SetState(KOOPAS_STATE_SHELL_MARIOSPIN);
						SetPosition(x - 15, y - 15);
					}
					if (koopas->GetState() == KOOPAS_STATE_SHELL && GetSpin() != 1)
					{

						if (this->hold == 1)
						{
							SetAniHolding(1);
							koopas->SetHolding(1);
						}

						else
						{
							//koopas->SetMarioKick(1);
							SetAniKick(1);
							StartKick();
							if (nx > 0)
								koopas->SetState(SHELL_STATE_WALKING_RIGHT);
							else
								koopas->SetState(SHELL_STATE_WALKING_LEFT);
						}
					}

				}

			}
			else if (dynamic_cast<CQuestionBlock*>(e->obj)) // if e->obj is Goomba 
			{
				CQuestionBlock* block = dynamic_cast<CQuestionBlock*>(e->obj);


				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny > 0)
				{
					if (block->GetState() == BLOCK_STATE_ACTIVITY)
					{
						block->SetState(BLOCK_STATE_INACTIVITY);
						/*block->StartUp();
						block->StartDown();*/

					}

				}
			}
			else if (dynamic_cast<CCoin*>(e->obj)) // if e->obj is Goomba 
			{

				CCoin* coin = dynamic_cast<CCoin*>(e->obj);
				// jump on top >> kill Goomba and deflect a bit 

				coin->SetState(COIN_STATE_DISAPPEAR);
				this->coin++;


			}
			else if (dynamic_cast<CBreakableBrick*>(e->obj)) // if e->obj is Goomba 
			{
				CBreakableBrick* brick = dynamic_cast<CBreakableBrick*>(e->obj);
				if (e->ny > 0)
				{
					brick->SetState(BRICK_STATE_DISAPPEAR);

				}
				if (e->nx != 0 && level == MARIO_LEVEL_TAIL && Spin == 1)
				{
					if (brick->x == 2366)
					{
						brick->SetTouch(1);
					}
					brick->SetState(BRICK_STATE_DISAPPEAR);

				}
				else
				{
					if (brick->GetState() == BRICK_STATE_COIN)
					{
						brick->SetState(BRICK_STATE_DISAPPEAR);
					}

				}
			}
			else if (dynamic_cast<CPbell*>(e->obj)) // if e->obj is Goomba 
			{
				CPbell* bell = dynamic_cast<CPbell*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					bell->SetState(BELL_STATE_INACTIVITY);
					bell->SetTouch(1);
					bell->StartPfeature();

				}

			}
			else if (dynamic_cast<CBall*>(e->obj)) // if e->obj is Goomba 
			{

				CBall* ball = dynamic_cast<CBall*>(e->obj);

				if (level == MARIO_LEVEL_SMALL)
					state = MARIO_STATE_DIE;
				else if (level == MARIO_LEVEL_BIG)
				{

					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}

			}
			else if (dynamic_cast<CCard*>(e->obj)) // if e->obj is Goomba 
			{

				CCard* card = dynamic_cast<CCard*>(e->obj);
				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny > 0 || e->nx != 0)
				{
					card->SetState(COIN_STATE_DISAPPEAR);
					this->card++;

				}
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}

			else if (dynamic_cast<CItem*>(e->obj))
			{
				CItem* item = dynamic_cast<CItem*>(e->obj);

				if (e->ny > 0 || Spin == 1)
				{
					item->SetTouch(1);
					//DebugOut(L"touch %d \n", item->GetTouch());
					if (item->x == 248 && item->y == 55)
					{
						item->y = 40;
						item->SetState(ITEM_STATE_MUSHROOM);
					}
					else if (item->x == 642 && id == 4)
					{
						item->y = 40;
						item->SetState(ITEM_STATE_GREENMUSHROOM);
					}
					else if (item->x == 1690 && item->y == 103 || item->x == 992)
					{
						item->y = 80;
						item->SetState(ITEM_STATE_LEAF);
					}
					else if (item->x == 1042)
					{
						item->SetState(ITEM_STATE_COINS);
						coin++;
						score++;
					}
					else
					{
						item->SetState(ITEM_STATE_COIN);
						coin++;
						score++;
					}

					/*}*/

				}
				else if (item->GetState() == ITEM_STATE_LEAF || item->GetState() == ITEM_STATE_MUSHROOM)
				{
					level++;
					score = score + 1000.0f;
					SetPosition(x, y - 16.0f);
					item->SetState(300);
				}


			}
			else if (dynamic_cast<CHoldBrick*>(e->obj)) // if e->obj is Goomba 
			{
				CHoldBrick* brick = dynamic_cast<CHoldBrick*>(e->obj);
				SetPosition(brick->x, brick->y);
				brick->SetState(BRICK_STATE_M);

			}
			else if (dynamic_cast<CMovingBrick*>(e->obj))
			{
				if (e->ny < 0)
				{

					CMovingBrick* movingPlattform = dynamic_cast<CMovingBrick*>(e->obj);
					movingPlattform->SetState(BRICK_STATE_FALLING);

				}

			}

			else if (dynamic_cast<CFlower*>(e->obj)) // if e->obj is Goomba 
			{

				CFlower* flower = dynamic_cast<CFlower*>(e->obj);
				StartUntouchable();
				if (nx > 0)
					SetPosition(x - 20, y);
				else if (nx < 0)
					SetPosition(x + 20, y);

				if (level == MARIO_LEVEL_SMALL)
				{
					state = MARIO_STATE_DIE;
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}

			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = 70;

	if (type == MARIO_TYPE_GREEN && isAppeared == true)
	{
		if (state == MARIO_STATE_WALKING_RIGHT)
		{
			ani = GREEN_MARIO_ANI_BIG_WALKING_RIGHT;
		}
		else if (state == MARIO_STATE_WALKING_LEFT)
			ani = GREEN_MARIO_ANI_BIG_WALKING_LEFT;
		else if (state == MARIO_STATE_IDLE)
		{
			if (nx > 0)
				ani = GREEN_MARIO_ANI_BIG_IDLE_RIGHT;
			else
				ani = GREEN_MARIO_ANI_BIG_IDLE_LEFT;

		}
		if (greenJump == 1 && nx > 0)
		{
			ani = GREEN_MARIO_ANI_JUMP_RIGHT;
		}
		else if (greenJump == 1 && nx < 0)
		{
			ani = GREEN_MARIO_ANI_JUMP_LEFT;
		}
	}
	else  if (isAppeared == true)
	{
		if (state == MARIO_STATE_DIE)
			ani = MARIO_ANI_DIE;

		else
		{
			if (level == MARIO_LEVEL_BIG)
			{

				if (state == MARIO_STATE_IDLE && jump != 1)
				{

					if (vx == 0)
					{
						if (nx > 0)
						{
							ani = MARIO_ANI_BIG_IDLE_RIGHT;
						}
						else ani = MARIO_ANI_BIG_IDLE_LEFT;
					}
				}

				else if (state == MARIO_STATE_SIT)
				{
					if (nx > 0)
						//ani = MARIO_ANI_BIG_SIT_RIGHT;
						ani = MARIO_ANI_BIG_BRAKING_LEFT;
					else /*if(nx<0)*/
						ani = MARIO_ANI_BIG_SIT_LEFT;
				}

				/*else if (state == MARIO_STATE_FAST_WALKING_LEFT)
				{
					ani = MARIO_ANI_BIG_WALKING_FAST_LEFT;
				}
				else if (state == MARIO_STATE_FAST_WALKING_RIGHT)
				{
					ani = MARIO_ANI_BIG_WALKING_FAST_RIGHT;
				}*/

				else
				{
					/* if (nx > 0 && vx < 0)
					{
						ani = MARIO_ANI_BIG_BRAKING_LEFT;
					}
					else if (nx < 0 && vx > 0)
					{
						ani = MARIO_ANI_BIG_BRAKING_RIGHT;
					}*/

					if (ny > 0 && nx > 0)
						ani = MARIO_ANI_BIG_JUMP_RIGHT;
					else if (ny > 0 && nx < 0)
						ani = MARIO_ANI_BIG_JUMP_LEFT;
					else if (aniHold == 1 && nx > 0)
					{
						ani = MARIO_ANI_BIG_HOLD_RIGHT;
					}
					else if (aniHold == 1 && nx < 0)
					{
						ani = MARIO_ANI_BIG_HOLD_LEFT;
					}
					else if (AniKick == 1 && nx > 0)
					{
						ani = MARIO_ANI_BIG_KICK_RIGHT;
					}
					else if (AniKick == 1 && nx < 0)
					{
						ani = MARIO_ANI_BIG_KICK_LEFT;
					}
					else if (jump == 1 && nx > 0)
					{
						ani = MARIO_ANI_BIG_JUMP_RIGHT;
					}
					else if (jump == 1 && nx < 0)
					{
						ani = MARIO_ANI_BIG_JUMP_LEFT;
					}
					else if (preFly == 1)
					{
						if (nx > 0)
							ani = MARIO_ANI_BIG_WALKING_FAST_RIGHT;
						else
							ani = MARIO_ANI_BIG_WALKING_FAST_LEFT;
					}

					else if (nx > 0)
						ani = MARIO_ANI_BIG_WALKING_RIGHT;
					else if (ny != 1)
						ani = MARIO_ANI_BIG_WALKING_LEFT;
				}
			}

			if (level == MARIO_LEVEL_SMALL)
			{
				if (state == MARIO_STATE_IDLE && jump != 1)
				{
					if (vx == 0)
					{
						if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
						else ani = MARIO_ANI_SMALL_IDLE_LEFT;

					}
				}
				else
				{
					if (ny > 0 && nx > 0)
						ani = MARIO_ANI_SMALL_JUMP_RIGHT;
					else if (aniHold == 1 && nx > 0)
					{
						ani = MARIO_ANI_SMALL_HOLD_RIGHT;
					}
					else if (aniHold == 1 && nx < 0)
					{
						ani = MARIO_ANI_SMALL_HOLD_LEFT;
					}
					else if (ny > 0 && nx < 0)
						ani = MARIO_ANI_SMALL_JUMP_LEFT;
					else if (jump == 1 && nx > 0)
					{
						ani = MARIO_ANI_SMALL_JUMP_RIGHT;
					}
					else if (jump == 1 && nx < 0)
					{
						ani = MARIO_ANI_SMALL_JUMP_LEFT;
					}

					else if (nx > 0)
						ani = MARIO_ANI_SMALL_WALKING_RIGHT;
					else if (nx < 0)
						ani = MARIO_ANI_SMALL_WALKING_LEFT;


				}
			}

			if (level == MARIO_LEVEL_TAIL)
			{


				if (CanFly == 1)
				{
					if (nx > 0) ani = MARIO_ANI_TAIL_FLY_RIGHT;
					else ani = MARIO_ANI_TAIL_FLY_LEFT;

				}
				if (state == MARIO_STATE_FLY)
				{
					if (nx > 0) ani = MARIO_ANI_TAIL_FLY_RIGHT;
					else ani = MARIO_ANI_TAIL_FLY_LEFT;
				}

				if (state == MARIO_STATE_IDLE && CanFly != 1 && Spin != 1 && jump != 1)
				{
					if (vx == 0)
					{
						if (nx > 0) ani = MARIO_ANI_TAIL_IDLE_RIGHT;
						else ani = MARIO_ANI_TAIL_IDLE_LEFT;
					}
				}
				else if (state == MARIO_STATE_SIT)
				{
					if (nx > 0)
						ani = MARIO_ANI_TAIL_SIT_RIGHT;
					else /*if(nx<0)*/
						ani = MARIO_ANI_TAIL_SIT_LEFT;
				}

				// chua sua dc van de lai
				else if (state == MARIO_STATE_FAST_WALKING)
				{
					if (nx > 0) ani = MARIO_ANI_TAIL_WALKING_FAST_RIGHT;
					else ani = MARIO_ANI_TAIL_WALKING_FAST_LEFT;
				}

				// 
				else if (/*state == MARIO_STATE_FAST_WALKING_LEFT*/ preFly == 1 && nx < 0 && CanFly != 0)
				{
					ani = MARIO_ANI_TAIL_WALKING_FAST_LEFT;
				}
				else if (/*state == MARIO_STATE_FAST_WALKING_RIGHT*/preFly == 1 && nx > 0 && CanFly != 10)
				{
					ani = MARIO_ANI_TAIL_WALKING_FAST_RIGHT;
				}

				else if (state == MARIO_STATE_FALL || state == RED_MARIO_STATE_FALL || checkFall == true)
				{
					if (nx > 0)
						ani = MARIO_ANI_TAIL_FALL_RIGHT;
					else /*if(nx<0)*/
						ani = MARIO_ANI_TAIL_FALL_LEFT;
				}
				else
				{

					if (aniHold == 1 && nx > 0 && CanFly != 1)
					{
						ani = MARIO_ANI_TAIL_HOLD_RIGHT;
					}
					else if (aniHold == 1 && nx < 0 && CanFly != 1)
					{
						ani = MARIO_ANI_TAIL_HOLD_LEFT;
					}
					if (Spin == 1)
					{
						ani = MARIO_ANI_TAIL_SPIN;
					}
					else if (jump == 1 && nx > 0 && checkFall != true)
					{
						ani = MARIO_ANI_TAIL_JUMP_RIGHT;
					}
					else if (jump == 1 && nx < 0 && checkFall != true)
					{
						ani = MARIO_ANI_TAIL_JUMP_LEFT;
					}

					else if (nx > 0 && CanFly != 1)
						ani = MARIO_ANI_TAIL_WALKING_RIGHT;
					else if (nx < 0 && CanFly != 1)
						ani = MARIO_ANI_TAIL_WALKING_LEFT;
				}
			}


			if (level == MARIO_LEVEL_FIRE)
			{
				if (state == MARIO_STATE_IDLE)
				{
					if (vx == 0)
					{
						if (nx > 0) ani = MARIO_ANI_FIRE_IDLE_RIGHT;
						else ani = MARIO_ANI_FIRE_IDLE_LEFT;
					}
				}

				//else if (state == MARIO_STATE_SIT)
				//{
				//	if (nx > 0)
				//		ani = MARIO_ANI_FIRE_SIT_RIGHT;
				//	else /*if(nx<0)*/
				//		ani = MARIO_ANI_FIRE_SIT_LEFT;
				//}
				else
				{
					if (ny > 0 && nx > 0)
						ani = MARIO_ANI_FIRE_JUMP_RIGHT;
					else if (ny > 0 && nx < 0)
						ani = MARIO_ANI_FIRE_JUMP_LEFT;
					else if (aniHold == 1 && nx > 0)
					{
						ani = MARIO_ANI_FIRE_HOLD_RIGHT;
					}
					else if (aniHold == 1 && nx < 0)
					{
						ani = MARIO_ANI_FIRE_HOLD_LEFT;
					}
					else if (jump == 1 && nx > 0)
					{
						ani = MARIO_ANI_FIRE_JUMP_RIGHT;
					}
					else if (jump == 1 && nx < 0)
					{
						ani = MARIO_ANI_FIRE_JUMP_LEFT;
					}
					else if (nx > 0)
						ani = MARIO_ANI_FIRE_WALKING_RIGHT;
					else
						ani = MARIO_ANI_FIRE_WALKING_LEFT;
				}
			}
		}
	}


	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		if (id == 3 /*|| id==4*/)
			vx = 0.08f;
		///*else if(id==4)
		//	vx = MARIO_WALKING_SPEED / 1.2;*/
		else if (id == 4)
		{
			vx = 0.12;
		}
		else
			vx = MARIO_WALKING_SPEED;
		nx = 1;
		ny = 0;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (id == 3 || id == 4)
			vx = -0.08;
		else
			vx = -MARIO_WALKING_SPEED;
		nx = -1;
		ny = 0;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		if (type == 1)
		{
			vy = -MARIO_JUMP_SPEED_Y / 120;
		}
		else if (id == 3 || id == 4)
			vy = -MARIO_JUMP_SPEED_Y / 1.2;
		else
			vy = -MARIO_JUMP_SPEED_Y;
		//ny = 1;
		break;

	case MARIO_STATE_IDLE:
		vx = 0;
		ny = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_SIT:
		vx = 0;
		ny = 0;
		break;
	case MARIO_STATE_FLY:
		vy = -MARIO_FLY_SPEED_Y * 1.35;
		vx = 0;
		ny = 1;
		if (nx > 0)
			vx = MARIO_WALKING_FAST_SPEED * 3.7;
		else
			vx = -MARIO_WALKING_FAST_SPEED * 3.7;
		break;
	case MARIO_STATE_FAST_WALKING:
		if (nx > 0)
		{
			if (vx < MARIO_WALKING_FAST_SPEED)
				vx = 0.5f * MARIO_WALKING_SPEED;
			else
				vx = MARIO_WALKING_FAST_SPEED;
		}
		else
		{
			if (vx < -MARIO_WALKING_FAST_SPEED)
				vx = -0.5f * MARIO_WALKING_SPEED;
			else vx = -MARIO_WALKING_FAST_SPEED;
		}
		break;
	case MARIO_STATE_HOLDKOOPAS:
		SetHolding(1);
		break;
	case MARIO_STATE_HIGHT_JUMP:
		if (type == 1)
		{
			vy = -MARIO_JUMP_SPEED_Y / 100;
		}
		else
			vy = -MARIO_JUMP_SPEED_Y;
		//ny = 1;
		break;

	case MARIO_STATE_SPIN:
		vx = 0;
		vy = 0;
		break;
	case MARIO_STATE_FAST_WALKING_LEFT:
		nx = -1;
		if (vx <= -0.4f)
		{
			vx = -0.4f;
		}
		else vx = -0.5f * MARIO_WALKING_SPEED + -0.015 * speedLevel;
		break;
	case GREEN_MARIO_STATE_JUMP_UP:
		nx = 1;
		vy = -MARIO_WALKING_SPEED;
		vx = MARIO_WALKING_SPEED / 1.5;

		break;
	case GREEN_MARIO_STATE_JUMP_DOWN:
		nx = 1;
		vy = MARIO_WALKING_SPEED;
		vx = MARIO_WALKING_SPEED / 1.5;

		break;
	case RED_MARIO_STATE_FALL:
		vy = MARIO_WALKING_SPEED / 2;
		vx = -MARIO_WALKING_SPEED;

		break;
	case MARIO_STATE_MOVE_DOWN:
		vy = MARIO_JUMP_SPEED_Y / 2.0f;
		vx = 0;
		break;
	case MARIO_STATE_MOVE_UP:
		vy = -MARIO_JUMP_SPEED_Y;
		vx = 0;
		break;
	case MARIO_STATE_MOVE_LEFT:
		vx = -MARIO_JUMP_SPEED_Y / 1.75f;
		nx = -1;
		ny = 0;
		break;
	case MARIO_STATE_MOVE_RIGHT:
		vx = MARIO_JUMP_SPEED_Y / 1.75f;
		nx = 1;
		ny = 0;
		vy = 0;
		break;
	case MARIO_STATE_FAST_WALKING_RIGHT:
		nx = 1;
		if (vx >= 0.4f)
		{
			vx = 0.4f;
		}
		else vx = 0.5f * MARIO_WALKING_SPEED + 0.015 * speedLevel;
	}


}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x;
	top = y;
	/*if (state == MARIO_STATE_SIT)
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}*/
	if (level == MARIO_LEVEL_TAIL)
	{
		if (nx > 0)
		{
			right = x + MARIO_BIG_BBOX_WIDTH +8;
		}else 
			right = x + MARIO_BIG_BBOX_WIDTH;

		bottom = y + MARIO_BIG_BBOX_HEIGHT;
		
	}
	else if (level != MARIO_LEVEL_SMALL /*&& state != MARIO_STATE_SIT*/)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}

	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}

}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

