#include "Keeper.h"
#include <iostream>
void Keeper::move(int dy,int dx){
    int r=field_->row(),
        c=field_->col(),
        new_r=r+dx,
        new_c=c+dy;
    if(!field_){
        cout<<"OMG, not connected to field!"<<endl;
        return;
    }
    if(!level_){
        cout<<"OMG, not connected to level!"<<endl;
        return;
    }
    LevelObject *o=level_->getObject(new_r,new_c);
    if(!o){
       level_->moveObject(r,c,new_r,new_c);
       std::cout<<"Moving...\n";
    }
    else if(o->type_name()=="Box"){
        level_->moveObject(new_r,new_c,new_r+dx,new_c+dy);
       level_->moveObject(r,c,new_r,new_c);
    };
}
