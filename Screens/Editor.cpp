#include "Editor.h"
#include "../Level/SokobanObjects.h"
int Editor::DispatchKey(const Keys &key){
    switch(key){
        case MOVE_LEFT:
            cursor->moveLeft();
            break;
        case MOVE_UP:
            cursor->moveUp();
            break;
        case MOVE_DOWN:
            cursor->moveDown();
            break;
        case MOVE_RIGHT:
            cursor->moveRight();
            break;
        case OPTION_1:
            level_->replaceObject(new Wall,cursor->y,cursor->x);
            break;
        case OPTION_2:
            level_->replaceObject(new Box,cursor->y,cursor->x);          
            break;
        case OPTION_3:
            level_->deleteObject(level_->getObject("Keeper"));
            level_->replaceObject(new Keeper,cursor->y,cursor->x);          
            break;
        case OPTION_4:
            level_->setMarked(cursor->y,cursor->x);
            break;
        case CONTROL_DELETE:
            level_->deleteObject(cursor->y,cursor->x);
            break;
        case CONTROL_SAVE:
            if(level_->validate())
                logic_->setScreen(&chooser);
            //level_->saveLevel("test.lvl");
            break;
        case CONTROL_CANCEL:
            logic_->setScreen(menu);
            return 0;
            break;
        default:
            return 0;
    }
    return 0;
    //eng_->ShowEditor(level_,cursor);
} 
