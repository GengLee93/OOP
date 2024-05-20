#pragma once
#include <vector>
#include <string>

#include "../Library/gameutil.h"

using namespace game_framework;

class UpdateCoins
{
private:
    CMovingBitmap coin_picture;
    std::vector<std::string> coinpic = {
        "Resources/coin1.bmp",
        "Resources/coin2.bmp",
        "Resources/coin3.bmp",
        "Resources/coin4.bmp",
        "Resources/coin5.bmp",
        "Resources/coin6.bmp",
        "Resources/coin7.bmp"
    };
    int coin_x;
    int coin_y;
public:
    UpdateCoins();

    CMovingBitmap Getpicture();
    void Setxy(int new_x, int new_y);
    void LoadCoin();
};
