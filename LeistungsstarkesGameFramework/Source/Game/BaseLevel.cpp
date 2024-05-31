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
        stairs_probability = {1, 0., 0, 0, 0, 0};
        stairs_speed = 3;
    }
    else if (level == 2)
    {
        // normal stair and fake stair
        stairs_probability = {0, 0.15, 0, 0, 0.05, 0.8};
        stairs_speed = 5;
    }
    else if (level == 3)
    {
        // normal stair, fake stair and conveyor
        stairs_probability = {0.4, 0.2, 0.1, 0.1, 0.1, 0.1};
        stairs_speed = 7;
    }
    else if (level == 4)
    {
        // normal stair, fake stair, conveyor and trampoline
        stairs_probability = {0.2, 0.2, 0.05, 0.05, 0.5, 0};
        stairs_speed = 6;
    }
    else if (level == 5)
    {
        // normal stair, fake stair, conveyor, trampoline and nail
        stairs_probability = {0, 0.3, 0.35, 0.35, 0, 0};
        stairs_speed = 6;
    }
    else if (level == 6)
    {
        stairs_probability = {0.2, 0.3, 0.1, 0.1, 0.2, 0.2};
        stairs_speed = 8;
    }
    else if (level == 7)
    {
        stairs_probability = {0.65, 0, 0.1, 0.1, 0.05, 0.1};
        stairs_speed = 7;
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

bool BaseLevel::isLoseOrWin(int select_level, int score)
{
    if(select_level == 1 && score >= 30)
    {
        return 1;
    }
    else if(select_level == 2 && score == 150)
    {
        return 1;
    }
    else if(select_level == 3 && score == 150)
    {
        return 1;
    }
    else if(select_level == 4 && score == 200)
    {
        return 1;
    }
    else if (select_level == 5 && score == 150)
    {
        return 1;
    }
    else if(select_level == 6 && score == 250)
    {
        return 1;
    }
    else if (select_level == 7 && score/80 == 100)
    {
        return 1;
    }
    else
    {
        return false;
    }
}



