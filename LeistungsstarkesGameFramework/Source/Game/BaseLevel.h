#pragma once
#include <vector>
#include <string>

#include "../Library/gameutil.h"

using namespace game_framework;

class BaseLevel
{
private:
    double stairs_probability[6];
    int stairs_speed;
public:
    BaseLevel(const double* stairs_probability, int stairs_speed);
    virtual ~BaseLevel(){}
    virtual void startGame() = 0;
};
