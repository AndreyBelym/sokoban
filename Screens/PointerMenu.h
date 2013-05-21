#pragma once
#include "Menu.h"
template <typename T>
struct PointerMenuElem: public MenuElem{
    //template <typename T>
    T *parent;
    void (T::*TSelectAction)();
    void SelectAction(GameLogic *l){
        (parent->*TSelectAction)();
    }
};

template <typename T>
struct PointerMenu: public Menu{
    T *parent;
    void (T::*TExitAction)();
    void ExitAction(){
        (parent->*TExitAction)();
    }
};
/*
template <typename T>
struct TypedMenu:public Menu{
    PointerMenuElem<T> subMenu[80];
};
*/
