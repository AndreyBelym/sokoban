#pragma once
#include "GameLogic.h"
#include "../Screens/PointerMenu.h"
#include "../Screens/LevelScreen.h"
#include "../Screens/Editor.h"
#include "../Screens/SizeSelect.h"
#include "../Screens/FileMenu.h"
#include "../Screens/WinScreen.h"
#include "../Screens/HallOfFame.h"
#include "../Level/SokobanLevel.h"
class SokobanLogic:public GameLogic{
    public:
    SokobanLevel level_;
    LevelScreen levscreen_;
    Editor editor_;
    SizeSelect select_;
    FileMenu<SokobanLogic> filemenu_;
    WinScreen winscreen_;
    HallOfFame fame_;
    struct StartMenu:public SimpleMenu{
        struct NG:public PointerMenuElem<SokobanLogic>{
            NG(){text="New game";}
        } NEW_GAME;
        
        struct LDG:public PointerMenuElem<SokobanLogic>{
            LDG(){text="Load game";}
        } LOAD_GAME;

        struct SE:public PointerMenuElem<SokobanLogic>{
             SE(){text="Editor";}
        } START_EDITOR;    

        struct EX:public MenuElem{
            EX(){text="Exit";}
            void SelectAction(GameLogic *l){
                l->stop();
            }
        } EXIT;

        StartMenu(){
            elements_.push_back(&NEW_GAME);
            elements_.push_back(&LOAD_GAME);
            elements_.push_back(&START_EDITOR);
            elements_.push_back(&EXIT);
        }

        void ExitAction(){logic_->stop();};
    } START_MENU;

    void LevelScreenSelectAction(){
        clog<<"setpath"<<endl;
        filemenu_.setPath("./",".lvl");
        clog<<"Show"<<endl;
        setScreen(&filemenu_);
        clog<<"OK"<<endl;
    }
    void SavedGameSelectAction(){
        filemenu_.setPath("./",".sav");
        setScreen(&filemenu_);
    }
    void EditorSelectAction(){
        setScreen(&select_);
    }
    void SelectLevel(){
        level_.loadLevel(filemenu_.filename.c_str());
        if(!level_.validate()){
            ShowStart();
            return;
        }
        levscreen_.steps_count=0;
        levscreen_.keeper=dynamic_cast<Keeper*>(level_.getObject("Keeper"));
        levscreen_.name=(filemenu_.name);
        setScreen(&levscreen_);
    }
    void ShowStart(){
        setScreen(&START_MENU);
    }
    SokobanLogic(){
        START_MENU.START_EDITOR.TSelectAction=&SokobanLogic::EditorSelectAction;
        START_MENU.NEW_GAME.TSelectAction=&SokobanLogic::LevelScreenSelectAction;
        START_MENU.LOAD_GAME.TSelectAction=&SokobanLogic::SavedGameSelectAction;
        
        filemenu_.parent=START_MENU.LOAD_GAME.parent=START_MENU.NEW_GAME.parent=START_MENU.START_EDITOR.parent=this;
        filemenu_.TExitAction=&SokobanLogic::ShowStart;

        fame_.logic_=levscreen_.chooser.logic_=editor_.chooser.logic_=winscreen_.logic_=filemenu_.logic_=START_MENU.logic_=levscreen_.logic_=editor_.logic_=select_.logic_=this;
        fame_.prev=winscreen_.menu=levscreen_.menu=editor_.menu=&START_MENU;
        levscreen_.win=&fame_;//&winscreen_;
        levscreen_.level=select_.level=&level_;
        editor_.setLevel(&level_);
        select_.nextscreen=&editor_;
        filemenu_.TSelectAction=&SokobanLogic::SelectLevel;
        setScreen(&START_MENU);
    }
}; 
