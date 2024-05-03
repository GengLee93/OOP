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

#include "UpdateStairs.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

// constexpr size_t min_stairs_id = 0;
// constexpr size_t max_stairs_id = 5;
constexpr size_t min_x_coordinate = 150;
constexpr size_t max_x_coordinate = 610;


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
	
	for (int i = 0; i < 9; ++i)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::vector<double> probabilities = {0.8, 0, 0.1, 0.1, 0, 0};
		std::discrete_distribution<> dis(probabilities.begin(), probabilities.end());
		stairs[i].Setxy(stairs[i].Getx(), stairs[i].Gety() - 3);
	
		//  generate stairs
		if (stairs[i].Gety() < 180)
		{
			UpdateStairs block;
			// block.SetID(rand() % (max_stairs_id - min_stairs_id + 1) + min_stairs_id);
			block.SetID(dis(gen));
			const int random_x = rand() % (max_x_coordinate - min_x_coordinate + 1) + min_x_coordinate;
			stairs[i] = block;
			stairs[i].Setxy(random_x, 1500);
		}
		if (CMovingBitmap::IsOverlap(player, stairs[i].Getpicture()))
		{
			vy = 0;
			gy = 0;
			if (stairs[i].GetID() == 0) {
				player.SetTopLeft(player.GetLeft(), stairs[i].Gety()- player.GetWidth() - 5);
			}else if (stairs[i].GetID() == 1) {
				samenail2 = samenail;
				samenail = i;
				touchnail = true;
				if(samenail == samenail2 || samenail == 10 ) {
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
				gy = -11;
			}
		}
	}
	player.SetTopLeft(player.GetLeft(), player.GetTop() + gy);

	// when life=0 or player is overlaping with ceiling, the game is over
	touchcei2  = touchcei;
	touchcei = CMovingBitmap::IsOverlap(player,ceiling);
	
	if (touchcei && !touchcei2)
	{
		player.SetTopLeft(player.GetLeft(),player.GetTop()+150);
		gy = 1;
		life -= 1;
		
		// 尚未解決如何從mygame_run 跳到 mygame_over
	}
	
	// player 左右移動
	if(rbKeyPressed)
	{
		if( player.GetLeft() <= 720 )
			player.SetTopLeft(player.GetLeft() + 9,player.GetTop());
	}
	else if (lbKeyPressed){
		if(player.GetLeft() >= 100  )
			player.SetTopLeft(player.GetLeft() - 9,player.GetTop());
	}
	vy += 1;
	if (vy % 2 == 0)
	{
		gy += 1;
	}
}

void CGameStateRun::OnInit() 							// 遊戲的初值及圖形設定
{
	// game background
	background.LoadBitmapByString({"Resources/background.bmp"});
	background.SetTopLeft(100, 150);
	
	// wall
	for (size_t i = 0; i < 2; i++)
	{
		wall[i].LoadBitmapByString({"Resources/wall.bmp"});
		wall[i].SetTopLeft(75 + 700 * i, 150);
	}

	// ceiling
	ceiling.LoadBitmapByString({"Resources/ceiling.bmp"}, RGB(255, 255, 255));
	ceiling.SetTopLeft(100, 150);

	// stairs
	srand(size_t(time(NULL)));
	for (size_t i = 0; i < 9; i++) 
	{
		UpdateStairs block;
		const int random_x = rand() % (max_x_coordinate - min_x_coordinate + 1) + min_x_coordinate;
		block.SetID(0); // init 9 normal blocks
		block.Getpicture();
		block.Setxy(random_x, 400 + i * 150);
		stairs.push_back(block);
		// 400 620 740 860, max = 850
	}
	
	player.LoadBitmapByString({"Resources/p1.bmp","Resources/p2.bmp","Resources/p3.bmp","Resources/p4.bmp","Resources/p5.bmp"},RGB(255, 255, 255));
	player.SetFrameIndexOfBitmap(0);
	player.SetTopLeft(450, 180);

	life = 10;
}
	

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// 偵測左右鍵是否按下
	switch (nChar)
	{
		case VK_LEFT:
			lbKeyPressed = true;
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
			rbKeyPressed = true;
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
		lbKeyPressed = false;
		break;
	case VK_RIGHT:
		rbKeyPressed = false;
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
	
	background.ShowBitmap();
	ceiling.ShowBitmap();
	for (size_t i = 0; i < 2; i++)
	{
		wall[i].ShowBitmap();
	}

	for (auto& stair : stairs) {
		if (CMovingBitmap::IsOverlap(stair.Getpicture(), background) && !stair.GetHidden()) {
			stair.Getpicture().ShowBitmap();
		}
	}
	if (CMovingBitmap::IsOverlap(player, background))
	{
		player.ShowBitmap();
	}
	if (player.GetTop() > 850 || life == 0)
	{
		GotoGameState(GAME_STATE_OVER);
		stairs.clear();
		for (size_t i = 0; i < 9; i++) 
		{
			UpdateStairs block;
			int random_x = rand() % (max_x_coordinate - min_x_coordinate + 1) + min_x_coordinate;
			block.SetID(0);
			block.Getpicture();
			block.Setxy(random_x, 400 + i * 150);
			stairs.push_back(block);
		}
		player.SetTopLeft(450, 180);
		lbKeyPressed = false;
		rbKeyPressed = false;
		life = 10;
		gy = 0;
	}
}

void CGameStateRun::draw_text()
{
	CDC *pDC = CDDraw::GetBackCDC();
	
	// print life
	CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
	std::string life_text;
	life_text = "Life " + std::to_string(life);
	CTextDraw::Print(pDC, 900, 150, life_text);

	// print HI
	CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
	std::string HI_text;
	HI_text = "HI " + std::to_string((HI));
	CTextDraw::Print(pDC, 900, 200, HI_text);
	
	CDDraw::ReleaseBackCDC();
}


	
	