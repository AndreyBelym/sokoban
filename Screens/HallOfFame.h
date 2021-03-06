#pragma once
#include "FileNameChooser.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
class RecordEntry:public InputField{
  public:
    int place;
    string name;
    int score;
    ostringstream str;
    RecordEntry(){
       visible=false;active=false;place=1;score=9000;name="<YourName>";
       update();
    } 
    void update(){
        str.str("");
        str<<place<<". "<<name<<"    "<<score;
        text=str.str();
        str.str("");
    }
    friend istream& operator>>(istream& is,RecordEntry &r){
        return is>>r.place>>r.name>>r.score;
    }
    friend ostream& operator<<(ostream& os,const RecordEntry &r){
        return os<<r.place<<" "<<r.name<<" "<<r.score<<endl;
    }
    RecordEntry(const RecordEntry &other):InputField(other)
    {
        name=other.name;
        score=other.score;
        visible=false;active=false;place=1;
        update();
    }
        
    void operator=(const RecordEntry& other){
        //place=other.place;
        InputField::operator=(other);
        //visible=other.visible;
        //active=other.active;
        name=other.name;
        score=other.score;
    }
    void addChar(char ch){
        text=name;
        InputField::addChar(ch);
        if(ch=='\r'||ch=='\n')
            if(!text.length())
                text="Anonymous";
        name=text;
        update();
    }
};
namespace fs=boost::filesystem;
class HallOfFame:public Menu{
  private:
    string filename_,name_,extension_;
  public:
    int current_score;
    static const int MAX_ENTRIES=13;  
    vector<RecordEntry> entries;
    PointerMenuElem<HallOfFame> ok;
    Screen *prev;
    int new_record;
    HallOfFame(){
        init();
        //load();
    }
    void setName(const string &name){
        name_=name;
        updateFilename();
    }
    void setExtension(const string& extension){
        extension_=extension;
        updateFilename();
    }
        
    void updateFilename(){
        filename_=name_+extension_;
    }

    void init(){
        ok.parent=this;
        ok.text="OK";
        ok.TSelectAction=&HallOfFame::ExitAction;
        new_record=MAX_ENTRIES;
        entries.clear();
        entries.resize(MAX_ENTRIES);
        for(int i=0;i<entries.size();++i){
            entries[i].place=i+1;
            entries[i].update();
            entries[i].visible=false;
            entries[i].active=false;
        }
        current_=MAX_ENTRIES;
    }
    void load(){
        //if(!fs::exists("records.txt"))
        //    return;

        ifstream ifs(filename_.c_str());
        if(!ifs.good())
            return;
        for(int i=0;i<MAX_ENTRIES;++i){
            entries[i].visible=false;
        }
        RecordEntry temp;
        temp.visible=true;
        while(!ifs.eof()){
            ifs>>temp;
            int place=temp.place-1;
            entries[place]=temp;
            entries[place].update();
        }
        ifs.close();
    }
    void save(){
        ofstream ofs(filename_.c_str());
        for(int i=0;i<MAX_ENTRIES&&entries[i].visible;++i){
            ofs<<entries[i];
        }
        ofs.close();
    }
    void setCurrentScore(int score){
        if(new_record!=MAX_ENTRIES)
            entries[new_record].active=false;
        current_score=score;
        for(int i=0;i<MAX_ENTRIES;++i){
            if(entries[i].visible&&entries[i].score<=current_score)
                continue;
            else {
                new_record=i;
                current_=i;
                for(int j=MAX_ENTRIES-1;j>i;--j){
                    entries[j]=entries[j-1];
                    entries[j].update();
                }
                entries[i].name="<Yourname>";
                entries[i].active=true;
                entries[i].visible=true;
                entries[i].score=current_score;
                entries[i].update();
                return;
            }
        }
    }
    int DispatchKey(const Keys &key){
        switch(key){
            case CONTROL_RAWINPUT:
                if(new_record==MAX_ENTRIES)
                    return 0;
                entries[new_record].addChar(logic_->engine()->getRawInput());
                return 0;
                break;
            //case MOVE_DOWN:
            //case MOVE_UP:
            //        if(current==MAX_ENTRIES)
            //            current=new_record;
            //        else
            //            current=MAX_ENTRIES;
            //    return 0;
            //    break;
            default:
                return Menu::DispatchKey(key);
                break;
       }
    }
    int size(){
        return MAX_ENTRIES+1;
    }
    MenuElem* element(int n){
        if(n>=0&&n<MAX_ENTRIES){
            return &entries[n];
        } else if (n==MAX_ENTRIES){
            return &ok;
        } else {
            return 0;
        }
    }
    void ExitAction(){
        save();
        logic_->setScreen(prev);
    };
};
