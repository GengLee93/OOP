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
// �o��class���C�����C���}�Y�e������
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
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	// ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	//
	// Sleep(1000);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
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
			GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
			break;
		}
	}
}

void CGameStateInit::OnShow()
{
	for (auto& level : levels)
	{
		level.ShowBitmap();
	}
	draw_text();
}

void CGameStateInit::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();

	/* Print title */
	CTextDraw::ChangeFontLog(pDC, 44, "�L�n������", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 290, 231, "�p�B�ͤU�ӱ�");

	/* Print info */
	CTextDraw::ChangeFontLog(pDC,  34, "�L�n������", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 282, 531, "Choose Level to Start");

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

