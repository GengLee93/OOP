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
	std::vector<std::string> stairs_image = {
		"Resources/nails.bmp",
		"Resources/normal.bmp",
		"Resources/conveyor_left2.bmp",
		"Resources/conveyor_right2.bmp",
		"Resources/fake2.bmp",
		"Resources/trampoline2.bmp"
	};
	int min = 0;
	int max = 5;
	int min_x = 150;
	int max_x = 650;
	for (int i = 0; i < 9; ++i)
	{
		stairs[i].SetTopLeft(stairs[i].GetLeft(), stairs[i].GetTop() - 3);

		if (stairs[i].GetTop() < 180)
		{
			// 隨機產生新磚塊類型
			unsigned int j = rand() % (max - min + 1) + min;

			// 創建新磚塊至尾部
			CMovingBitmap block;
			block.LoadBitmapByString({stairs_image[j]}, RGB(255, 255, 255));
			unsigned x = rand() % (max_x - min_x + 1) + min_x;
			stairs[i] = block;
			stairs[i].SetTopLeft(x, 1100);
		}
		if (CMovingBitmap::IsOverlap(player, stairs[i]))
		{
			if (stairs[i].GetImageFileName() == "Resources/normal.bmp") {
				player.SetTopLeft(player.GetLeft(), stairs[i].GetTop() - player.GetWidth() - 5);
			}else if (stairs[i].GetImageFileName() == "Resources/nails.bmp") {
				player.SetTopLeft(player.GetLeft(), stairs[i].GetTop() - player.GetWidth() - 5);
			}else if (stairs[i].GetImageFileName() == "Resources/conveyor_left2.bmp") {
				player.SetTopLeft(player.GetLeft() - 5, stairs[i].GetTop() - player.GetWidth() - 5);
			} else if (stairs[i].GetImageFileName() == "Resources/conveyor_right2.bmp") {
				player.SetTopLeft(player.GetLeft() + 5, stairs[i].GetTop() - player.GetWidth() - 5);
			} else if (stairs[i].GetImageFileName() == "Resources/fake2.bmp") {
				fakeStairActivated = true;
				player.SetTopLeft(player.GetLeft(), player.GetTop() + 2);
			}else if (stairs[i].GetImageFileName() == "Resources/trampoline2.bmp") {
				player.SetTopLeft(player.GetLeft(), stairs[i].GetTop() - player.GetWidth() - 5);
			}
		}else {
			player.SetTopLeft(player.GetLeft(), player.GetTop() + 2);
		}
	}

	// when life=0 or player is overlaping with ceiling, the game is over
	if (CMovingBitmap::IsOverlap(player, ceiling))
	{
		// 尚未解決如何從mygame_run 跳到 mygame_over
	}
}

void CGameStateRun::OnInit() 							// 遊戲的初值及圖形設定
{
	// 遊戲背景
	background.LoadBitmapByString({"Resources/background.bmp"});
	background.SetTopLeft(100, 150);

	// 牆
	for (size_t i = 0; i < 2; i++)
	{
		wall[i].LoadBitmapByString({"Resources/wall.bmp"});
		wall[i].SetTopLeft(75 + 700 * i, 150);
	}

	// 天花板
	ceiling.LoadBitmapByString({"Resources/ceiling.bmp"}, RGB(255, 255, 255));
	ceiling.SetTopLeft(100, 150);
	
	srand(size_t(time(NULL)));
	size_t min_x = 150;
	size_t max_x = 650;
	for (size_t i = 0; i < 9; i++) // init 9 normal blocks
	{
		CMovingBitmap block;
		size_t x = rand() % (max_x - min_x + 1) + min_x;
		block.LoadBitmapByString({"Resources/normal.bmp"});
		block.SetTopLeft(x, 300 + i * 100);
		stairs.push_back(block);
	}
	
	player.LoadBitmapByString({"Resources/p1.bmp"}, RGB(255, 255, 255));
	player.SetTopLeft(450, 100);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
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
	background.ShowBitmap();
	ceiling.ShowBitmap();
	for (size_t i = 0; i < 2; i++)
	{
		wall[i].ShowBitmap();
	}
	for (size_t i = 0; i < stairs.size(); i++)
	{
		if (CMovingBitmap::IsOverlap(stairs[i], background)) 
		{
			if (stairs[i].GetImageFileName() == "Resources/nails.bmp" && fakeStairActivated)
			{
				continue;
			}
			stairs[i].ShowBitmap();
		}
	}
	if (CMovingBitmap::IsOverlap(player, background))
	{
		player.ShowBitmap();
	}
}
	
	