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
		"Resources/conveyor_left.bmp",
		"Resources/conveyor_right.bmp",
		"Resources/fake.bmp",
		"Resources/trampoline.bmp"
	};
	for (int i = 0; i < 9; ++i)
	{
		stairs[i].SetTopLeft(stairs[i].GetLeft(), stairs[i].GetTop() - 5);
	}
	if (stairs[0].GetTop() < 150)
	{
		// 隨機產生新磚塊類型
		int min=0;
		int max=5;
		unsigned int i = rand() % (max - min + 1) + min;

		// 創建新磚塊志尾部
		//CMovingBitmap newStair;
		stairs[0].LoadBitmapByString({stairs_image[i]});
		stairs[0].SetTopLeft(stairs[i].GetLeft(), stairs[i].GetTop());
		//stairs.push_back(newStair);
	}
	
	
}

void CGameStateRun::OnInit() 							// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({"Resources/background.bmp"});
	background.SetTopLeft(100, 150);
	
	for (int i = 0; i < 2; i++)
	{
		wall[i].LoadBitmapByString({"Resources/wall.bmp"});
		wall[i].SetTopLeft(75 + 700 * i, 150);
	}
	
	ceiling.LoadBitmapByString({"Resources/ceiling.bmp"}, RGB(255, 255, 255));
	ceiling.SetTopLeft(100, 150);

	srand(size_t(time(NULL)));
	int min_x = 150;
	int max_x = 650;
	for (int i = 0; i < 9; i++)
	{
		CMovingBitmap block;
		unsigned int x = rand() % (max_x - min_x + 1) + min_x;
		block.LoadBitmapByString({"Resources/normal.bmp"});
		block.SetTopLeft(x, 300 + i*100);
		stairs.push_back(block);
	}
	
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
		for (int i = 0; i < 2; i++)
		{
			wall[i].ShowBitmap();
		}
		for (unsigned int i = 0; i < stairs.size(); i++)
		{
			if (CMovingBitmap::IsOverlap(stairs[i], background)) // stairs only show on the background
			{
				stairs[i].ShowBitmap();
			}
		}
	}
	
	