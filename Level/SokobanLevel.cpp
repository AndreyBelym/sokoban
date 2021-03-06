#include "SokobanLevel.h"
SokobanLevel::SokobanLevel():box_count(0),
               mark_count(0),
               keeper_count(0)
{};
bool SokobanLevel::attachObject(LevelObject *obj,int row,int col){
    cout<<"attaching object"<<endl;
    if(Level::attachObject(obj,row,col)){
        std::string type=obj->type_name();
        if(type=="Keeper")
            keeper_count++;
        else if(type=="Box")
            box_count++;
        return true;
    } else
        return false;
}
LevelObject* SokobanLevel::detachObject(int row,int col){
    LevelObject *obj=Level::detachObject(row,col);
    if(obj){
        std::string type=obj->type_name();
        if(type=="Keeper")
            keeper_count--;
        else if(type=="Box")
            box_count--;
    }
    return obj;
}        
LevelObject* SokobanLevel::replaceObject(LevelObject *obj,int row,int col,bool destroy){
    cout<<"replacing object"<<endl;
    LevelObject *temp=Level::replaceObject(obj,row,col,false);
    std::string type;
    if(obj&&obj->level()==this){
        type=obj->type_name();
        if(type=="Keeper")
            keeper_count++;
        else if(type=="Box")
            box_count++;
    }
    if(temp){   
        type=temp->type_name();
        if(type=="Keeper")
            keeper_count--;
        else if(type=="Box")
            box_count--;
        if(destroy){
            delete temp;
            temp=0;
        }
    }
    return temp;
}     
bool SokobanLevel::setMarked(int row,int col,bool val){        
    if(Level::setMarked(row,col,val)){
        val?mark_count++:mark_count--;
        return true;
    }
    return false;
}

std::istream& SokobanLevel::load(std::istream& is){
    Level::load(is);
    for(int i=0;i<rows;++i)
        for(int j=0;j<cols;++j){
            if(fields(i,j).marked()){
                cout<<"new mark"<<endl;
                mark_count++;
            }
            if(!fields(i,j).object())
                continue;
            std::string type=fields(i,j).object()->type_name();
            if(type=="Keeper")
                keeper_count++;
            else if(type=="Box")
                box_count++;
        }
    return is;
}
bool SokobanLevel::validate(){
    cout<<"k: "<<keeper_count
        <<"m: "<<mark_count
        <<"b: "<<box_count<<endl;
    return keeper_count==1&&(mark_count==box_count);
}
void SokobanLevel::clear(){
    Level::clear();
    keeper_count=0;
    mark_count=0;
    box_count=0;
}
