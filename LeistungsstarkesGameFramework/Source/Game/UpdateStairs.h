#pragma once
#include <vector>
#include <string>

#include "../Library/gameutil.h"

using namespace game_framework;

class UpdateStairs {
private:
    std::vector<std::string> stairs_image = {
        "Resources/normal.bmp",
        "Resources/nails.bmp",
        "Resources/conveyor_left2.bmp",
        "Resources/conveyor_right2.bmp",
        "Resources/fake2.bmp",
        "Resources/trampoline2.bmp"
    };
    CMovingBitmap spicture;
    unsigned id;     
    bool isHidden = false;
    int x;
    int y;
    
public:
    UpdateStairs();
    
    virtual CMovingBitmap Getpicture();
    virtual void SetID(unsigned new_id);
    void SetHidden(bool isHidden);
    virtual void Setxy(int new_x, int new_y);
    int Getx();
    int Gety();
    unsigned GetID();
    bool GetHidden();
};
