#include "stdafx.h"
#include "UpdateCoins.h"

UpdateCoins::UpdateCoins() {}


CMovingBitmap UpdateCoins::Getpicture()
{
    return this->coin_picture;
}

void UpdateCoins::Setxy(int new_x, int new_y)
{
    coin_x = new_x;
    coin_y = new_y;
    this->coin_picture.SetTopLeft(coin_x, coin_y);
}

void UpdateCoins::LoadCoin()
{
    coin_picture.LoadBitmapByString({this->coin_images}, RGB(255, 255, 255));
}
void UpdateCoins::ismove(bool s)
{
    if(s)
    {
        this->coin_picture.SetAnimation(50,false);
    }
}




