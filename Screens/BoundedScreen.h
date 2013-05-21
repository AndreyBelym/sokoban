#pragma once
#include "Screen.h"
#include "../Logic/GameLogic.h"
class BoundedScreen: public Screen{
    public:  
    GameLogic *logic_;
    public:
    BoundedScreen():logic_(0){}
    BoundedScreen(GameLogic *logic):logic_(logic){};
    void setLogic(GameLogic *logic){logic_=logic;}
};
