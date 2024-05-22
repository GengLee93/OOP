#pragma once
#include <vector>
#include <string>

#include "../Library/gameutil.h"

using namespace game_framework;

class UpdateCoins
{
private:
    CMovingBitmap coin_picture;
    std::vector<std::string> coin_images = {
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
    bool isHidden = false;
public:
    UpdateCoins();

    
    void LoadCoinBitmap();
    void Setxy(int x, int y);
    void SetHidden(bool isHidden);
    void ismove(bool s);
    CMovingBitmap Getpicture();
    bool GetHidden();
    
};
