#pragma once
#include <vector>
#include <string>

#include "../Library/gameutil.h"

using namespace game_framework;

class UpdateStairs : public CMovingBitmap {
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
    size_t id;              // ¹Ï¤ù½s¸¹
    bool isHidden = false;
    int x;
    int y;
    
public:
    UpdateStairs();
    
    CMovingBitmap Getpicture();
    void SetID(size_t new_id);
    void SetHidden(bool isHidden);
    void Setxy(int new_x, int new_y);
    int Getx();
    int Gety();
    size_t GetID();
    bool GetHidden();
};
