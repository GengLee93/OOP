#include "stdafx.h"
#include "UpdateCoins.h"

UpdateCoins::UpdateCoins() {}


CMovingBitmap UpdateCoins::Getpicture()
{
    return coin_picture;
}

void UpdateCoins::Setxy(int new_x, int new_y)
{
    coin_x = new_x;
    coin_y = new_y;
    coin_picture.SetTopLeft(coin_x, coin_y);
}

void UpdateCoins::LoadCoin()
{
    coin_picture.LoadBitmapByString(this->coinpic, RGB(255, 255, 255));
}



