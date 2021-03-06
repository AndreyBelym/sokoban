#include "Field.h" 
#include "LevelObjectFactory.h"
void Field::setRow(int row){row_=row;}
void Field::setCol(int col){col_=col;}
void Field::setMarked(bool m){marked_=m;}
void Field::deleteObject()const{
    delete detachObject();
}
LevelObject* Field::detachObject()const{
    cout<<"Field::detachObject()!"<<row_<<","<<col_<<endl;        
    LevelObject *temp=obj;
    if(temp){
        //temp->setLevel(0);
        temp->setField(0);
    }
    obj=0;
    cout<<"Field::detachObject()!"<<endl;        
    return temp;
}
LevelObject* Field::replaceObject(LevelObject *new_obj,bool destroy){
    LevelObject *lo=detachObject();
    if(!attachObject(new_obj)){
        attachObject(lo);
        return 0;
    }
    if (lo&&destroy){
        delete lo;
        lo=0;    
    };
    return lo;
}

LevelObject* Field::replaceObject(const std::string& type_name,bool destroy){
    return replaceObject(LevelObjectFactory::create(type_name),destroy);
}

bool Field::attachObject(LevelObject* new_obj)const{
    if(obj||!new_obj){
        cout<<"attach object failed!"<<endl;
        return false;
    }
    obj=new_obj;
    obj->setField(this);
    return true;
}
bool Field::addObject(const std::string& type_name)const{
    return attachObject(LevelObjectFactory::create(type_name));
};
Field::Field(){obj=0;row_=0;col_=0;marked_=false;}
Field::Field(const Field& other){
    obj=0;
    cout<<"Field(const Field&)!"<<endl;        
    LevelObject *obj=other.detachObject();
    cout<<"~Field(const Field&):"<<obj<<endl;        
    attachObject(obj);
    row_=other.row_;
    col_=other.col_;
    marked_=other.marked_;
    cout<<"Field(const Field&)!"<<endl;        
}
void Field::operator=(const Field& other){
    cout<<"Field::operator=(const Field&)!"<<endl;        
    LevelObject *obj=other.detachObject();
    cout<<"Field::operator=(const Field&):"<<obj<<endl;        
    attachObject(obj);
    row_=other.row_;
    col_=other.col_;
    marked_=other.marked_;
    cout<<"Field::operator=(const Field&)!"<<endl;        
}
Field::~Field(){
    cout<<"~Field()!"<<row_<<","<<col_<<endl;        
    deleteObject();
    cout<<"~Field()!"<<endl;        
}
std::ostream& operator<<(std::ostream &os,const Field& f){
    if(f.obj)
        os<<*f.obj;
    else
        os<<"None";
    os<<" "
      <<f.marked_<<" "
      <<f.row_<<" "
      <<f.col_<<endl;
    return os;
}
std::istream& operator>>(std::istream& is,Field &f){
    LevelObject *new_obj;
    is>>new_obj;
    is>>f.marked_
      >>f.row_
      >>f.col_;
    f.attachObject(new_obj);
    return is;
}
LevelObject* Field::object(){return obj;};
bool Field::marked()const{return marked_;}
int Field::row()const{return row_;}
int Field::col()const{return col_;}
