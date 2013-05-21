#include "LevelScreen.h"
#include <cstdlib>
int LevelScreen::DispatchKey(const Keys &key){
    switch(key){
        case MOVE_LEFT:
            keeper->moveLeft();
            steps_count++;
            break;
        case MOVE_UP:
            keeper->moveUp();
            steps_count++;
            break;
        case MOVE_DOWN:
            keeper->moveDown();
            steps_count++;
            break;
        case MOVE_RIGHT:
            keeper->moveRight();
            steps_count++;
            break;
        case CONTROL_SAVE:
            //level->saveLevel("test.lvl");
            logic_->setScreen(&chooser);
            break;
        case CONTROL_CANCEL:
            logic_->setScreen(menu);
            return 0;
            break;
        default:
            return 0;
    }
    //eng_->ShowLevel(level);
    if(level->check("Box")){
        logic_->showScreen();
        win->setExtension(".rec");        
        win->setName(name);
        win->load();
        win->setCurrentScore(steps_count);
        logic_->setScreen(win);
        return 0;
    }
    return 0;
}; 
