#pragma once
#include <vector>
#include <string>

#include "../Library/gameutil.h"
#include "UpdateStairs.h"


class UpdateCoins : public UpdateStairs
{
private:
    CMovingBitmap coin_picture;
    int coin_x;
    int coin_y;
public:
    UpdateCoins();

    CMovingBitmap Getpicture() override;
    void SetID(unsigned id) override;
    void Setxy(int new_x, int new_y) override;
};
