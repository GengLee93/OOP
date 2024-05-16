#include "stdafx.h"
#include "BaseLevel.h"

BaseLevel::BaseLevel()
{
}

void BaseLevel::SetLevel(int level)
{
    if (level == 1)
    {
        // normal stair
        stairs_probability = {1, 0, 0, 0, 0, 0};
        stairs_speed = 4;
    }
    if (level == 2)
    {
        // normal stair and fake stair
        stairs_probability = {0.7, 0, 0, 0, 0.3, 0};
        stairs_speed = 4;
    }
    if (level == 3)
    {
        // normal stair, fake stair and conveyor
        stairs_probability = {0.55, 0, 0.075, 0.075, 0.3, 0};
        stairs_speed = 5;
    }
    if (level == 4)
    {
        // normal stair, fake stair, conveyor and trampoline
        stairs_probability = {0.55, 0, 0.075, 0.075, 0.2, 0.1};
        stairs_speed = 5;
    }
    if (level == 5)
    {
        // normal stair, fake stair, conveyor, trampoline and nail
        stairs_probability = {0.3, 0.25, 0.1, 0.1, 0.15, 0.1};
        stairs_speed = 6;
    }
    if (level == 6)
    {
        stairs_probability = {0.25, 0.25, 0.125, 0.125, 0.25, 0.1};
        stairs_speed = 6;
    }
}

unsigned BaseLevel::GetSpeed()
{
    return this->stairs_speed;
}

vector<double> BaseLevel::GetStairsProbability()
{
    return this->stairs_probability;
}

int BaseLevel::GetLevel()
{
    return this-> select_level;
}


