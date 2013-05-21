#pragma once
#include "../Screens/Screen.h"
#include "../Engine/GameEngine.h"
class GameLogic{
  public:
    GameLogic();
    ~GameLogic();
    void Main() const;
    void setEngine(GameEngine *e) const;
    void setScreen(Screen *s) const;
    void showScreen() const;
    void stop() const;
    void setRawInput(bool s=true){eng_->modeRawInput=s;}
    bool rawInput(){return eng_->modeRawInput;}
    GameEngine* engine(){return eng_;}
  protected:
    mutable GameEngine* eng_;
    mutable Screen* screen_;
    mutable bool running_;
};
