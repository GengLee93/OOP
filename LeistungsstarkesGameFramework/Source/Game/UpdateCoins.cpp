#include "stdafx.h"
#include "UpdateCoins.h"

UpdateCoins::UpdateCoins() {}


CMovingBitmap UpdateCoins::Getpicture()
{
    return this->coin_picture;
}

void UpdateCoins::Setxy(int x, int y)
{
    coin_x = x;
    coin_y = y;
    this->coin_picture.SetTopLeft(coin_x, coin_y);
}

void UpdateCoins::SetHidden(bool isHidden)
{
    this->isHidden = isHidden;
}

void UpdateCoins::LoadCoinBitmap()
{
    coin_picture.LoadBitmapByString({this->coin_images}, RGB(0, 0, 0));
}

void UpdateCoins::ismove(bool s)
{
    if(s)
    {
        this->coin_picture.SetAnimation(50,false);
    }
}

bool UpdateCoins::GetHidden()
{
    return this->isHidden;
}




