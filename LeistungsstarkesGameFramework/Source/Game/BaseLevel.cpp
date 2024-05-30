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
        stairs_probability = {0.99, 0., 0, 0, 0.01, 0};
        stairs_speed = 3;
    }
    else if (level == 2)
    {
        // normal stair and fake stair
        stairs_probability = {0.01, 0.18, 0, 0, 0., 0.81};
        stairs_speed = 5;
    }
    else if (level == 3)
    {
        // normal stair, fake stair and conveyor
        stairs_probability = {0.7, 0.1, 0.05, 0.05, 0.05, 0.05};
        stairs_speed = 6;
    }
    else if (level == 4)
    {
        // normal stair, fake stair, conveyor and trampoline
        stairs_probability = {0.2, 0.05, 0.01, 0.01, 0.58, 0.15};
        stairs_speed = 7;
    }
    else if (level == 5)
    {
        // normal stair, fake stair, conveyor, trampoline and nail
        stairs_probability = {0, 0.3, 0.35, 0.35, 0, 0};
        stairs_speed = 7;
    }
    else if (level == 6)
    {
        stairs_probability = {0.2, 0.35, 0.1, 0.1, 0.25, 0.1};
        stairs_speed = 8;
    }
    else if (level == 7)
    {
        stairs_probability = {0.6, 0, 0.1, 0.1, 0.1, 0.1};
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


