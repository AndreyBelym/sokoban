#ifndef MENU_H
#define MENU_H
#include <string>
#include "BoundedScreen.h"
#include "../Logic/GameLogic.h"
#include <vector>

struct MenuElem{
    std::string text;
    bool visible,active;
    virtual void SelectAction(GameLogic *l)=0;
    virtual ~MenuElem(){};
    MenuElem():text(""),visible(true),active(true){};
};
class Menu :public BoundedScreen{
  protected:
    int current_;
  public:
    Menu():current_(0){type=MENU;};
    virtual MenuElem* element(int n)=0;
    int currentNumber(){return current_;}
    MenuElem* current(){return element(current_);}
    virtual int size()=0;
    virtual void ExitAction()=0;
    virtual int DispatchKey(const Keys &key); 
    void next(){
        current_++;
        if(current_>=size()) 
            current_=0;
    }
    void prev(){
        --current_;
        if(current_<0)
            current_=size()-1;
    }
    virtual ~Menu(){};
};
class SimpleMenu:public Menu{
  protected:
      std::vector<MenuElem*> elements_;
  public:
    int size(){
        return elements_.size();
    }
    MenuElem* element(int n){
        if(n>=0&&n<elements_.size())
            return elements_[n];
        else
            return 0;
    }
};
#endif
