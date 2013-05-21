#pragma once
#include "Menu.h"
#include "../Level/Level.h"
#include <boost/filesystem.hpp>
#include <vector>
template <typename T>
class FileMenu: public PointerMenu<T>{
    private:
    std::string path_;
    std::vector<PointerMenuElem<FileMenu<T> > > elements_;
    public:
    std::string extension_;
    std::string name;
    std::string filename;
    using PointerMenu<T>::parent;
    using PointerMenu<T>::current_;
    void (T::*TSelectAction)();
    void clear(){
        elements_.clear();
    }
    void SelectFile(){
        name=PointerMenu<T>::current()->text;
        filename=name+extension_;
        (parent->*TSelectAction)();
        clear();
    }
    void setPath(const char* path,
                 const char *extension){
        clear();
        path_=string(path);
        extension_=string(extension);
        update();
    }
    void update(){
        boost::filesystem::directory_iterator end_itr; 
        int count=0;
        for( boost::filesystem::directory_iterator i( path_ ); i != end_itr; ++i )
        {
            if( !boost::filesystem::is_regular_file( i->status() ) ) continue;
            if( i->path().extension()!=extension_) continue;
            PointerMenuElem<FileMenu> new_fe;
            new_fe.text=i->path().stem().string();
            new_fe.TSelectAction=&FileMenu::SelectFile;
            new_fe.parent=this;
            elements_.push_back(new_fe);
            count++;
        }
    }
    int size(){
        return elements_.size();
    }
    MenuElem* element(int n){
        if(n>=0&&n<elements_.size())
            return &elements_[n];
        else return 0;
    }
};    
