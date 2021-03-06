#pragma once
#include "PointerMenu.h"
class InputField: public MenuElem{
    public:
    GameLogic *l_;
    void SelectAction(GameLogic *l){
        l_=l;
        l->setRawInput();
    }

    void addChar(char ch){
        if(ch=='\n'||ch=='\r'){
            l_->setRawInput(false);
            return;
        } else if(ch=='\b'||ch=='\x7f'){
            if(text.length())
                text.erase(text.size()-1,1);
        }else if(isgraph(ch)){
            text+=ch;
        }
   }
};

template <typename T>
class FilenameChooser: public Menu{ 
  public:
    InputField field;
    PointerMenuElem<T> select;
    std::string &filename;
    FilenameChooser():filename(field.text){
        select.text="OK";
    };
    int size(){
        return 2;
    }
    MenuElem* element(int n){
        switch(n){
            case 0:
                return &field;
            case 1:
                return &select;
            default:
                return 0;
        }
    }
    int DispatchKey(const Keys &key){
        if (logic_->rawInput()){
            if(key==CONTROL_RAWINPUT)
                field.addChar(logic_->engine()->getRawInput());
            return 0;
        } else 
            return Menu::DispatchKey(key);
    }
    void ExitAction(){};
};


