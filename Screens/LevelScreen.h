#pragma once
#include "BoundedScreen.h"
#include "WinScreen.h"
#include "../Level/Level.h"
#include "Menu.h"
#include "FileNameChooser.h"
#include "HallOfFame.h"
#include "../Level/SokobanObjects.h"


class LevelScreen:public BoundedScreen{
  public:
    int steps_count;
    Level *level;
    string name;
    Menu *menu;
    HallOfFame *win;
    Keeper *keeper;
    FilenameChooser<LevelScreen> chooser;
    void SaveLevel(){
        level->saveLevel(chooser.filename.c_str());
        logic_->setScreen(this);
    }
    LevelScreen(){
        steps_count=0;
        type=LEVELSCREEN;
        chooser.select.parent=this;
        chooser.select.TSelectAction=&LevelScreen::SaveLevel;
    };
    int DispatchKey(const Keys &key);
};
