#include "stdafx.h"
#include "player.h"


player::player(int life, int x, int y, int id) : life(life), x(x), y(y), id(id){}
void player::SetPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

int player::Getlife()
{
    return life;
}

void player::Setlife(int newlife)
{
    life = newlife;    
}



