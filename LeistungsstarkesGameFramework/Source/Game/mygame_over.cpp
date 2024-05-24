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
	
}

void CGameStateOver::OnShow()
{
	draw_text();
}

void CGameStateOver::draw_text()
{
	CDC *pDC = CDDraw::GetBackCDC();

	/* Print title */
	CTextDraw::ChangeFontLog(pDC, 44, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 290, 228, "結束");

	if(select_level == 7)
	{
		CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
		std::string coin_text;
		coin_text = "coin " + std::to_string(int(coin_point/50));
		CTextDraw::Print(pDC, 290, 600, coin_text);
		CDDraw::ReleaseBackCDC();

	}
	else
	{
		CTextDraw::ChangeFontLog(pDC, 30, "微軟正黑體", RGB(255, 255, 255));
		std::string HI_text;
		HI_text = "Score " + std::to_string(HI);
		CTextDraw::Print(pDC, 290, 600, HI_text);
		CDDraw::ReleaseBackCDC();
	}
	
}
void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_INIT);
}



