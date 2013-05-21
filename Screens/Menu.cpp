#include "Menu.h"
int Menu::DispatchKey(const Keys &key){
    switch(key){
        case MOVE_RIGHT:
            element(current_)->SelectAction(logic_);
            return 0;
            break;
        case MOVE_UP:
            do{
                prev();
            } while(!element(current_)->active);
            break;
        case MOVE_DOWN:
            do{
                next();
            }while(!element(current_)->active);
            break;
        case CONTROL_CANCEL:
        case MOVE_LEFT:
            ExitAction();
            return 0;
            break;
        default:
            return 0;
    }
    //eng_->ShowMenu(menu);
    return 0;
};
