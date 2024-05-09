#include "stdafx.h"
#include "BaseLevel.h"

BaseLevel::BaseLevel(const double* stairs_probability, int stairs_speed): stairs_speed(stairs_speed)
{
    for (int i=0; i<6; ++i)
    {
        this->stairs_probability[i] = stairs_probability[i];
    }
}
