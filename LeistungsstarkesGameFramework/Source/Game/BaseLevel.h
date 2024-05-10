#pragma once
#include <vector>
#include <string>

#include "../Library/gameutil.h"

using namespace game_framework;

class BaseLevel
{
private:
    std::vector<double> stairs_probability;
    int stairs_speed = 1;
public:
    BaseLevel();
    
    void startGame();
    void SetLevel(int h);
    
    unsigned GetSpeed();
    vector<double> GetStairsProbability();
};
