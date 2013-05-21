#include "List.h"
#include "cstdlib"
#include <iostream>
using namespace std;
List::List():first(NULL),
             last(NULL),
             current(NULL)
{
}

List::List(const char* source):first(NULL),
                               last(NULL),
                               current(NULL)
{
    FromChar(source);
}

void List::Next() const{
    if(current&&current->next)
        current=current->next;
}

char List::Value() const{
    if(current)
        return current->c;
    else
        return '\0';
}

void List::Reset() const{
    current=first;
}

bool List::isEnd() const{
    return current==last||current->next==NULL||current==NULL;
}

void List::Append(char new_char){
    Elem* new_elem=new (nothrow) Elem;
    if(new_elem==NULL){
       cerr<<"Error of memory allocation for new element!"<<endl;
       return;
    } 
    if(last!=NULL)
        last->next=new_elem;
    else {
        first=new_elem;
        current=new_elem;
    }
    last=new_elem;;
    last->next=NULL;
    last->c=new_char;
}
void List::Prepend(char new_char){
    Elem* new_elem=new (nothrow) Elem;
    if(new_elem==NULL){
       cerr<<"Error of memory allocation for new element!"<<endl;
       return;
    }
    if(first==NULL){
        last=new_elem;
        current=new_elem;
    };
    new_elem->next=first;
    first=new_elem;
    first->c=new_char;
}

void List::FromChar(const char* source){
    const char* ptr=source;
    for(ptr;*ptr;ptr++){
        Append(*ptr);
    }
}
void List::Clear(){
    current=first;
    if(current==NULL);
        return;
    Elem *prev=current;
    while(!isEnd()){
        Next();
        delete prev;
        prev=current;
    }
    delete prev;
    current=first=last=NULL;
}
List::~List(){
    Clear();    
}

void List::Print() const{
    Elem* backup=current;
    Reset();
    while(!isEnd()){
        std::cout<<Value();
        Next();
    }
    std::cout<<Value()<<std::endl;
    current=backup;
}

void List::Delete(){
    if(!current)
        return;
    Elem* tmp_next=current->next;
    if(tmp_next){
        current->c=current->next->c;
        current->next=current->next->next;
        delete tmp_next;
    } else {
        if(current==first) {
            first=NULL;
            last=NULL;
            current=NULL;
            delete tmp_next;
        } else {
            Reset();
            while(current->next&&current->next->next)
                Next();
            current->next=NULL;
            last=current;
            delete tmp_next;
        }
    }
}

void List::DeleteNext(){
    if(!current)
        return;
    Elem* tmp_next=current->next;
    if(tmp_next){
        current->next=current->next->next;
        delete tmp_next;
    } else
        current->next=NULL;
}

void List::Insert(char c){
    if(current==NULL)
        Prepend(c);
    Elem* new_elem=new (nothrow) Elem;
    if(new_elem==NULL)
        std::cout<<"malloc error"<<std::endl;
    new_elem->c=current->c;
    new_elem->next=current->next;
    current->c=c;
    current->next=new_elem;
    if(current==last)
        last=new_elem;

}

void List::InsertNext(char c){
    if(current==NULL||current==last)
        Append(c);
    Elem* new_elem=new (nothrow) Elem;
    if(new_elem==NULL)
        return;
    new_elem->c=c;
    new_elem->next=current->next;
    current->next=new_elem;
}
void List::Copy(const List& other){
    if(this==&other)
        return;
    Clear();
    Elem* backup=other.current;
    other.Reset();
    while(!other.isEnd()){
        Append(other.Value());
        other.Next();
    }
    Append(other.Value());
    other.current=backup;    
};

List::List(const List& other):first(NULL),
                              last(NULL),
                              current(NULL)
{
    Copy(other);
}

List& List::operator=(const List& other){
    Copy(other);
    return *this;
}
