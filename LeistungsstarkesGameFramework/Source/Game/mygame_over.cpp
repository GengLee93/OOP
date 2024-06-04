#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	
}

void CGameStateOver::OnBeginState()
{
	
}

void CGameStateOver::OnInit()
{
	over.LoadBitmapByString({"Resources/picover.bmp"});
	win.LoadBitmapByString({"Resources/picwin.bmp"});
	over.SetTopLeft(380,130);
	win.SetTopLeft(380,130);
	
}

void CGameStateOver::OnShow()
{
	draw_text();
	if(isWin)
	{
		win.ShowBitmap();
	}
	else
	{
		over.ShowBitmap();
	}
	
}

void CGameStateOver::draw_text()
{
	CDC *pDC = CDDraw::GetBackCDC();

	if(select_level == 7)
	{
		CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
		std::string coin_text;
		coin_text = " coin point :" + std::to_string(int(coin_point/80));
		CTextDraw::Print(pDC, 500, 600, coin_text);
		CDDraw::ReleaseBackCDC();

	}
	else
	{
		CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
		std::string HI_text;
		HI_text = "Score " + std::to_string(HI);
		CTextDraw::Print(pDC, 560, 600, HI_text);
		CDDraw::ReleaseBackCDC();
	}
	
}
void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	isWin =false;
	GotoGameState(GAME_STATE_INIT);
}



