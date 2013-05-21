#pragma once
#include "BoundedScreen.h"
#include <cstdio>
#include "Menu.h"
class WinScreen:public BoundedScreen{
    public:
    Menu *menu;
    std::string text;
    std::string caption;
    WinScreen():text("CONGRATULATIONS! YOU WINRAR!"),
                caption("VICTORY!")
        {type=WIN_SCREEN;};
    int DispatchKey(const Keys &key){
        printf("Olololo\n");
        logic_->setScreen(menu);
        return 0;
    }
};
