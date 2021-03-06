#pragma once
#include <typeinfo>
#include <iostream>
#include "GameEngine.h"
#include "../Screens/Menu.h"
#include "../Screens/Editor.h"
#include "../Screens/LevelScreen.h"
#include "../Screens/WinScreen.h"

class BaseGameEngine: public GameEngine{
    virtual void showScreen(Screen *s){
        if(s->type==Screen::MENU){
                showMenu(dynamic_cast<Menu*>(s));
        } else if(s->type==Screen::EDITOR){
                showEditor(dynamic_cast<Editor*>(s));
        } else if(s->type==Screen::LEVELSCREEN){
                showLevelScreen(dynamic_cast<LevelScreen*>(s));
        } else if(s->type==Screen::WIN_SCREEN){
                showWin(dynamic_cast<WinScreen*>(s));
        } else {
            std::cerr<<"Fuck!"<<std::endl;
        }
    }
    virtual void showMenu(Menu *m)=0;
    virtual void showLevelScreen(LevelScreen *l)=0;
    virtual void showEditor(Editor *l)=0;
    virtual void showSizeEditor()=0;
    virtual void showWin(WinScreen *w)=0;
    virtual void showLose()=0; 
};
