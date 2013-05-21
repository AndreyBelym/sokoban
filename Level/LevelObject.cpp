#include "LevelObject.h"
void LevelObject::setLevel(Level *level){
    level_=level;
}

void LevelObject::setField(const Field *field){
    field_=field;
}

LevelObject::~LevelObject(){
    cout<<"~LevelObject()!"<<endl;
    cout<<"~LevelObject()!"<<endl;

};

std::ostream& operator<<(std::ostream& os,const LevelObject& obj){
    return obj.printTo(os);
}

std::ostream& LevelObject::printTo(std::ostream& os)const {
    os<<type_name();
    return overridedPrintTo(os);
}

const Field* LevelObject::field()const{
    return field_;
}

Level* LevelObject::level()const{
    return level_;
}

std::ostream& LevelObject::overridedPrintTo(std::ostream& os)const{
    return os;
};

std::istream& LevelObject::overridedInputFrom(std::istream& is){
    return is;
}
