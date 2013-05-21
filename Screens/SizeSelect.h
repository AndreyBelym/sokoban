#pragma once
#include "Menu.h"
#include <string>
#include <sstream>
struct CounterElem: public MenuElem{
    private:
    std::string name_;
    std::ostringstream format;
    public:
    int value;
    CounterElem():value(0){};
    void inc(){value++;updateText();};
    void dec(){if(value>0){value--;updateText();}}
    void SelectAction(GameLogic *l){inc();}
    void updateText(){
        format.str("");
        format<<name_<<": "<<value;
        text=format.str();
        format.str("");        
    }
    void setName(const std::string &name){
        name_=name;
        updateText();
    }
};

class SizeSelect:public SimpleMenu{
    public:
    int rows,cols;
    Level *level;
    Screen *nextscreen;
    CounterElem rows_counter,cols_counter;
    PointerMenuElem<SizeSelect> next;
    void NextAction(){
        level->setSize(rows_counter.value,cols_counter.value);
        logic_->setScreen(nextscreen);
    }
    SizeSelect(){
        rows_counter.setName("Rows count");
        cols_counter.setName("Colums count");
        next.text="OK";

        next.parent=this;
        next.TSelectAction=&SizeSelect::NextAction;

        elements_.push_back(&rows_counter);
        elements_.push_back(&cols_counter);
        elements_.push_back(&next);

    }
    int DispatchKey(const Keys &key){
        if(current_==0
            &&key==MOVE_LEFT){
            rows_counter.dec();
            return 0;
        } else if (current_==1&&key==MOVE_LEFT) {
            cols_counter.dec();
            return 0;
        } else 
            return Menu::DispatchKey(key);
    }
    void ExitAction(){};
};
