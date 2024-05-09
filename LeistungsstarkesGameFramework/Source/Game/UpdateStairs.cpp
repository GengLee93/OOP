#include "stdafx.h"
#include "UpdateStairs.h"

UpdateStairs::UpdateStairs() {}


CMovingBitmap UpdateStairs::Getpicture()
{
    return spicture;
}

void UpdateStairs::SetID(unsigned new_id)
{
    this->id = new_id;
    if (id < 6)
    {
        spicture.LoadBitmapByString({stairs_image[this->id]}, RGB(255, 255, 255));
    }
}

void UpdateStairs::SetHidden(bool isHidden)
{
    this->isHidden = isHidden;
}

void UpdateStairs::Setxy(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
    spicture.SetTopLeft(x, y);
}


unsigned UpdateStairs::GetID()
{
    return this->id;
}

int UpdateStairs::Getx()
{
    return this->x;
}

int UpdateStairs::Gety()
{
    return this->y;
}

bool UpdateStairs::GetHidden()
{
    return this->isHidden;
}
