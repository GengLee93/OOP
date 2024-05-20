#include "stdafx.h"
#include "UpdateCoins.h"

UpdateCoins::UpdateCoins() {}


CMovingBitmap UpdateCoins::Getpicture()
{
    return coin_picture;
}

void UpdateCoins::SetID(unsigned id)
{
    coin_picture.LoadBitmapByString({
        "Resources/coin1.bmp",
        "Resources/coin2.bmp",
        "Resources/coin3.bmp",
        "Resources/coin4.bmp",
        "Resources/coin5.bmp",
        "Resources/coin6.bmp",
        "Resources/coin7.bmp"
    }, RGB(255, 255, 255));
}

void UpdateCoins::Setxy(int new_x, int new_y)
{
    new_x = this->coin_x;
    new_y = this->coin_y;
    coin_picture.SetTopLeft(new_x, new_y);
}


