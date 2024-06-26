#pragma once
#include <vector>
#include <string>

#include "../Library/gameutil.h"
#include "UpdateStairs.h"

using namespace game_framework;

class BaseLevel
{
private:
    std::vector<double> stairs_probability;
    int stairs_speed;
    int select_level;
public:
    BaseLevel();
    
    void SetLevel(int level);
    unsigned GetSpeed();
    vector<double> GetStairsProbability();
    int GetLevel();
    bool isLoseOrWin(int select_level, int score);
};
