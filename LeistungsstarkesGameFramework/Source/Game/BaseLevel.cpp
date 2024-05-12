#include "stdafx.h"
#include "BaseLevel.h"

BaseLevel::BaseLevel()
{
}

void BaseLevel::SetLevel(int h)
{
    if (h == 1)
    {
        stairs_probability = {1, 0, 0, 0, 0, 0};
    }
    if (h == 2)
    {
        stairs_probability = {0.8, 0, 0, 0, 0.2, 0};
        stairs_speed = 2;
    }
    if (h == 3)
    {
        stairs_probability = {0.55, 0.15, 0.075, 0.075, 0.1, 0.05};
        stairs_speed = 2;
    }
    if (h == 4)
    {
        stairs_probability = {0.55, 0.15, 0.075, 0.075, 0.1, 0.05};
        stairs_speed = 3;
    }
    if (h == 5)
    {
        stairs_probability = {0.3, 0.25, 0.1, 0.1, 0.15, 0.1};
        stairs_speed = 3;
    }
    if (h == 6)
    {
        stairs_probability = {0.25, 0.25, 0.125, 0.125, 0.25, 0.1};
        stairs_speed = 4;
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


