#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <vector>
#include <string>

#include "BaseLevel.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

std::vector<std::string> levels_images = {
	"Resources/level1.bmp",
	"Resources/level2.bmp",
	"Resources/level3.bmp",
	"Resources/level4.bmp",
	"Resources/level5.bmp",
	"Resources/level6.bmp",
	"Resources/level7.bmp"
};

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	for (unsigned i = 0; i < levels_images.size(); i++)
	{
		levels[i].LoadBitmapByString({levels_images[i]}, RGB(255, 255, 255));
		levels[i].SetTopLeft((i + 1) * 150, 700);
	}
	prtostr.LoadBitmapByString({"Resources/ptstart.bmp"},RGB(255, 255, 255));
	prtostr.SetTopLeft(540,560);
	NSHAFT.LoadBitmapByString({"Resources/NS.bmp"},RGB(255, 255, 255));
	NSHAFT.SetTopLeft(340, 260);
	invic.LoadBitmapByString({"Resources/invi.bmp", "Resources/nrmo.bmp"},RGB(255, 255, 255));
	invic.SetTopLeft(1300,20);
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	for (unsigned i = 0; i < levels_images.size(); i++)
	{
		if (is_overlap(levels[i], point))
		{
			select_level = i + 1;
			coin_point  = 0;
			GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
			break;
		}
	}
	if (is_overlap(invic, point) && invic.GetFrameIndexOfBitmap() == 0)
	{
		isinvic = 1;
		invic.SetFrameIndexOfBitmap(1);
	}
	else if(is_overlap(invic, point) && invic.GetFrameIndexOfBitmap() == 1)
	{
		isinvic = 0;
		invic.SetFrameIndexOfBitmap(0);
	}
}

void CGameStateInit::OnShow()
{
	for (auto& level : levels)
	{
		level.ShowBitmap();
	}
	prtostr.ShowBitmap();
	NSHAFT.ShowBitmap();
	invic.ShowBitmap();
	draw_text();
}

void CGameStateInit::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();

	// /* Print title */
	// CTextDraw::ChangeFontLog(pDC, 44, "微軟正黑體", RGB(255, 255, 255));
	// CTextDraw::Print(pDC, 290, 231, "小朋友下樓梯");

	// /* Print info */
	// CTextDraw::ChangeFontLog(pDC,  34, "微軟正黑體", RGB(255, 255, 255));
	// CTextDraw::Print(pDC, 282, 531, "Choose Level to Start");

	CDDraw::ReleaseBackCDC();
}

bool CGameStateInit::is_overlap(CMovingBitmap bitmap, CPoint point)
{
	int obj_left = bitmap.GetLeft();
	int obj_right = bitmap.GetLeft() + bitmap.GetWidth();
	int obj_top = bitmap.GetTop();
	int obj_bottom = bitmap.GetTop() + bitmap.GetHeight();
	if (point.x >= obj_left && point.x < obj_right && point.y > obj_top && point
		.y < obj_bottom)
	{
		return true;
	}
	return false;
}

