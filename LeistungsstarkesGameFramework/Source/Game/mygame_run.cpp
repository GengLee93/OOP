#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <iostream>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>
#include <random>
#include <thread>

#include "UpdateStairs.h"
#include "BaseLevel.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////


CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)		
{
}


CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<double> probabilities;

	// random x
	std::uniform_int_distribution<> dis_x(150, 610);
	
	// choose level
	
	level.SetLevel(select_level);
	probabilities = level.GetStairsProbability();
	std::discrete_distribution<> dis(probabilities.begin(), probabilities.end());
	
	for (int i = 0; i < 9; ++i)
	{
		
		stairs[i].Setxy(stairs[i].Getx(), stairs[i].Gety() - level.GetSpeed());
		if (select_level == 7) 
		{
			coin_mark.SetTopLeft(stairs[6].Getx() + 30 ,stairs[6].Gety() - 45);
		}
		if(CMovingBitmap::IsOverlap(player,coin_mark))
		{
			k = 1;
			coin_point += 1;
		}
		
		// generate stairs
		if (stairs[i].Gety() < 180)
		{
			score += 1;
			if(score % 1 == 0 && life < 15)
			{
				life += 1;
			}
			UpdateStairs block;
			block.SetID(dis(gen));
			stairs[i] = block;
			stairs[i].Setxy(dis_x(gen), 1500);
		}
		
		if (CMovingBitmap::IsOverlap(player, stairs[i].Getpicture()))
		{
			velocity_y = 0;
			gravity_y = 0;
			if (stairs[i].GetID() == 0) {
				player.SetTopLeft(player.GetLeft(), stairs[i].Gety()- player.GetWidth() - 5);
			}else if (stairs[i].GetID() == 1) {
				same_nail2 = same_nail;
				same_nail = i;
				touchnail = true;
				if(same_nail == same_nail2 || same_nail == 10 ) {
					touchnail = false;
				}
				if (touchnail) {
					life -= 1;
					touchnail = false;
				}
				player.SetTopLeft(player.GetLeft(), stairs[i].Gety() - player.GetWidth() - 1);
			}else if (stairs[i].GetID() == 2) {
				player.SetTopLeft(player.GetLeft() - 5, stairs[i].Gety() - player.GetWidth() - 5);
			} else if (stairs[i].GetID() == 3) {
				player.SetTopLeft(player.GetLeft() + 5, stairs[i].Gety() - player.GetWidth() - 5);
			} else if (stairs[i].GetID() == 4) {
				stairs[i].SetHidden(true);
				player.SetTopLeft(player.GetLeft(), player.GetTop() + 2);
			}else if (stairs[i].GetID() == 5) {
				player.SetTopLeft(player.GetLeft(), stairs[i].Gety() - player.GetWidth() - 5);
				gravity_y = -10;
			}
		}
		
	}
	touching_ceiling2  = touching_ceiling;
	touching_ceiling = CMovingBitmap::IsOverlap(player,ceiling);
	if (touching_ceiling && !touching_ceiling2)
	{
		player.SetTopLeft(player.GetLeft(),player.GetTop()+150);
		gravity_y = 1;
		life -= 1;
	}
	
	// player movement
	player.SetTopLeft(player.GetLeft(), player.GetTop() + gravity_y);
	if(right_key_pressed)
	{
		if( player.GetLeft() <= 720)
			player.SetTopLeft(player.GetLeft() + 9,player.GetTop());
	}
	else if (left_key_pressed){
		if(player.GetLeft() >= 100)
			player.SetTopLeft(player.GetLeft() - 9,player.GetTop());
	}
	velocity_y += 1;
	if (velocity_y % 2 == 0)
	{
		gravity_y += 1;
	}
	
	wait += 1;
	if(wait % 120 == 119)
	{
		k = 0;
		wait = 0; 
	}
}

void CGameStateRun::OnInit() 							// 遊戲的初值及圖形設定
{
	// game background
	background.LoadBitmapByString({
		"Resources/background.bmp",
		"Resources/ocean.bmp",
		"Resources/whie.bmp",
		"Resources/mount.bmp",
		"Resources/lr.bmp",
		"Resources/uiverse.bmp",
		"Resources/background.bmp"});
	background.SetTopLeft(100, 150);
	
	// wall
	for (unsigned i = 0; i < 2; i++)
	{
		walls[i].LoadBitmapByString({"Resources/wall.bmp"});
		walls[i].SetTopLeft(75 + 700 * i, 150);
	}

	// ceiling
	ceiling.LoadBitmapByString({"Resources/ceiling.bmp"}, RGB(255, 255, 255));
	ceiling.SetTopLeft(100, 150);

	// stairs & coin
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis_x(150, 610);
	for (unsigned i = 0; i < 9; i++) 
	{
		UpdateStairs block;
		block.SetID(0); // init 9 normal blocks
		block.Getpicture();
		block.Setxy(dis_x(gen), 400 + i * 150);
		stairs.push_back(block);
		
		// UpdateCoins coin;
		// coin.LoadCoinBitmap();
		// coin.Setxy(300,300);
		// coin.ismove(1);
		// coins.push_back(coin);
	}
	coin_mark.LoadBitmapByString({
			"Resources/coin1.bmp",
			"Resources/coin2.bmp",
			"Resources/coin3.bmp",
			"Resources/coin4.bmp",
			"Resources/coin5.bmp",
			"Resources/coin6.bmp",
			"Resources/coin7.bmp"
		}, RGB(0, 0, 0));
	coin_mark.SetAnimation(50, false);
	coin_mark.SetTopLeft(90, 90);
	
	
	// player
	player.LoadBitmapByString({
		"Resources/p1.bmp",
		"Resources/p2.bmp",
		"Resources/p3.bmp",
		"Resources/p4.bmp",
		"Resources/p5.bmp"}, RGB(255, 255, 255));
	player.SetTopLeft(450, 180);
	player.SetFrameIndexOfBitmap(0);

	coin_label.LoadBitmapByString({
			"Resources/coin1.bmp",
			"Resources/coin2.bmp",
			"Resources/coin3.bmp",
			"Resources/coin4.bmp",
			"Resources/coin5.bmp",
			"Resources/coin6.bmp",
			"Resources/coin7.bmp"
		}, RGB(0, 0, 0));
	coin_label.SetAnimation(50, false);
	coin_label.SetTopLeft(910, 205);

	blood.LoadBitmapByString({"Resources/blood.bmp"}, RGB(255, 242, 0));
	blood.SetTopLeft(915, 254);
}
	

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// 偵測左右鍵是否按下
	switch (nChar)
	{
		case VK_LEFT:
			left_key_pressed = true;
			if(player.GetImageFileName() == "Resources/p4.bmp")
			{
				player.SetFrameIndexOfBitmap(4);
			}
			else
			{
				player.SetFrameIndexOfBitmap(3);
			}
			break;
		case VK_RIGHT:
			right_key_pressed = true;
			if(player.GetImageFileName() == "Resources/p2.bmp")
			{
				player.SetFrameIndexOfBitmap(2);
			}
			else
			{
				player.SetFrameIndexOfBitmap(1);
			}
			break;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// 偵測左右鍵是否放開
	switch (nChar)
	{
	case VK_LEFT:
		left_key_pressed = false;
		break;
	case VK_RIGHT:
		right_key_pressed = false;
		break;
	}
	player.SetFrameIndexOfBitmap(0);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	draw_text();
	
	background.SetFrameIndexOfBitmap(select_level - 1);
	background.ShowBitmap();
	ceiling.ShowBitmap();
	blood.ShowBitmap();
	for (auto& wall : walls)
	{
		wall.ShowBitmap();
	}
	for (auto& stair : stairs)
	{
		/*
			In UpdateStairs.h, SetHidden() is initialized as false.
			When the player collides with a fake stair, it becomes True.
			This remains True until the next time the fake stair is re-initialized.
		*/
		if (CMovingBitmap::IsOverlap(stair.Getpicture(), background) && !stair.GetHidden()) {
			stair.Getpicture().ShowBitmap();
		}
	}
	if (select_level == 7 )
	{
		if(k == 0)
			coin_mark.ShowBitmap();
			coin_label.ShowBitmap();
	}
	
	if (CMovingBitmap::IsOverlap(player, background))
	{
		player.ShowBitmap();
	}

	// restart
	
	if (player.GetTop() > 850 || life == 0 )
	{
		restart_game();
	}
	if ((select_level == 7))
	{
		if(level.isLoseOrWin(7, int(coin_point)))
		{
			isWin =true;
			restart_game();
		}
	}
	else if (level.isLoseOrWin(select_level, score))
	{
		isWin = true;
		restart_game();
	}
		
}

void CGameStateRun::restart_game()
{
	stairs.clear();
	coins.clear();
	std::random_device rd;
	std::mt19937 gen(rd());
	for (int i = 0; i < 9; i++)
	{
		std::uniform_int_distribution<> dis_x(150, 610);
		UpdateStairs block;
		block.SetID(0);
		block.Getpicture();
		block.Setxy(dis_x(gen), 400 + i * 150);
		stairs.push_back(block);
	}
	player.SetTopLeft(450, 180);
	left_key_pressed = false;
	right_key_pressed = false;
	life = 5;
	gravity_y = 0;
	score = 0;
	wait = 0;
	k = false;
	GotoGameState(GAME_STATE_OVER);
}

void CGameStateRun::draw_text()
{
	CDC *pDC = CDDraw::GetBackCDC();
	
	// print Level
	CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
	std::string level;
	level = "Level " + std::to_string(select_level);
	CTextDraw::Print(pDC, 900, 150, level);

	if(select_level ==  7)
	{
		CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
		std::string coin_text;
		coin_text = "         " + std::to_string(int(coin_point/80)) + "/100";
		CTextDraw::Print(pDC, 900, 200, coin_text);
		
		
	}
	else 
	{
		// print HI
		CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
		std::string HI_text;
		HI = score;
		HI_text = "score " + std::to_string((HI));
		CTextDraw::Print(pDC, 900, 200, HI_text);
	}
	
	
	
	// print life
	CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
	std::string life_text;
	life_text ="         "+ std::to_string(life);
	CTextDraw::Print(pDC, 900, 250, life_text);
	
	
	
	CDDraw::ReleaseBackCDC();
}






	
	