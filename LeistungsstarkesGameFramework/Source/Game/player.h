#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

class player
{
public:
    int life;
    int x;
    int y;
    int id;
    
protected:
    player(int life, int x,int y,int id);
    void SetPosition(int newX, int newY);
    int Getlife();
    void Setlife(int newlife);
    
private:
   std::vector<std::string> pictures = {
       "Resources/p1.bmp",
       "Resources/p2.bmp",
       "Resources/p3.bmp",
       "Resources/p4.bmp",
       "Resources/p5.bmp"};
    
};
