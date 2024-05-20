#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <iostream>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <random>
#include <chrono>
#include <thread>

#include "UpdateStairs.h"
#include "UpdateCoins.h"
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
	BaseLevel level;
	level.SetLevel(select_level);
	probabilities = level.GetStairsProbability();
	std::discrete_distribution<> dis(probabilities.begin(), probabilities.end());
	
	for (int i = 0; i < 9; ++i)
	{
		stairs[i].Setxy(stairs[i].Getx(), stairs[i].Gety() - level.GetSpeed());
		// if (select_level == 7)
		// {
		// 	coins[i].Setxy(coins[i].Getx(), coins[i].Gety() - level.GetSpeed());
		// }
		
		// generate stairs
		if (stairs[i].Gety() < 180)
		{
			score += 1;
			if(score % 8 == 0 && life < 5)
			{
				life += 1;
			}
			UpdateStairs block;
			block.SetID(dis(gen));
			stairs[i] = block;
			stairs[i].Setxy(dis_x(gen), 1500);
			if (coins[i].Gety() < 180)
			{
				UpdateCoins coin;
				coin.SetID(6);
				coins[i] = coin;
				coins[i].Setxy(block.Getx() + 50, block.Gety() - 10);
			}
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
		"Resources/uiverse.bmp"});
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
		
		UpdateCoins coin;
		coin.SetID(7); // init 9 coins
		coin.Getpicture();
		coin.Setxy(block.Getx() + 50, block.Gety() - 10);
		coins.push_back(coin);
	}

	// player
	player.LoadBitmapByString({
		"Resources/p1.bmp",
		"Resources/p2.bmp",
		"Resources/p3.bmp",
		"Resources/p4.bmp",
		"Resources/p5.bmp"}, RGB(255, 255, 255));
	player.SetFrameIndexOfBitmap(0);
	player.SetTopLeft(450, 180);
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
	
	background.SetFrameIndexOfBitmap(1);
	background.ShowBitmap();
	ceiling.ShowBitmap();
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
	if (select_level == 7)
	{
		for (auto& coin : coins)
		{
			if (CMovingBitmap::IsOverlap(coin.Getpicture(), background) && !coin.GetHidden())
			{
				coin.Getpicture().ShowBitmap();
			}
		}
	}
	if (CMovingBitmap::IsOverlap(player, background))
	{
		player.ShowBitmap();
	}

	// restart
	if (player.GetTop() > 850 || life == 0)
	{
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

		UpdateCoins coin;
		coin.SetID(7); // init 9 coins
		coin.Getpicture();
		coin.Setxy(block.Getx() + 50, block.Gety() - 10);
		coins.push_back(coin);
	}
	player.SetTopLeft(450, 180);
	left_key_pressed = false;
	right_key_pressed = false;
	life = 5;
	gravity_y = 0;
	score = 0;
	coin_point = 0;
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

	// print HI
	CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
	std::string HI_text;
	HI = score;
	HI_text = "score " + std::to_string((HI));
	CTextDraw::Print(pDC, 900, 200, HI_text);
	
	// print life
	CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
	std::string life_text;
	life_text = "Life " + std::to_string(life);
	CTextDraw::Print(pDC, 900, 250, life_text);

	// coin
	if (select_level == 7)
	{
		CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
		std::string coin_text;
		coin_text = "      " + std::to_string(coin_point) + "/10";
		CTextDraw::Print(pDC, 900, 300, coin_text);
	}

	
	CDDraw::ReleaseBackCDC();
}






	
	