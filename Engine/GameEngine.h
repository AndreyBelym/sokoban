#pragma once
#include "../Screens/Screen.h"
#include "../Engine/Keys.h"
class GameEngine{
  protected:
    char rawInput;
  public:
    bool modeRawInput;  
    virtual void Init()=0;
    virtual Keys getKey()=0;
    virtual void showScreen(Screen *s)=0;
    virtual char getRawInput()=0;
    virtual void Stop()=0;
    virtual ~GameEngine(){};
    GameEngine():modeRawInput(false),rawInput('\0'){};
};    
