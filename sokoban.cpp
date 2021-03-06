#include <iostream>
#include "Logic/SokobanLogic.h"
#include "Engine/CursesEngine.h"
#include "Engine/SDLEngine.h"
#include <string>
#include <iostream>
#include <cstring>
#ifdef __unix__
#include "Platform/nix.h"
#elif _WIN32
#include "Platform/win.h"
#endif

using namespace std;

namespace fs=boost::filesystem;

int main(int argc,char **argv){
   //SokobanLogic l;
   fs::path path=fs::path(argv[0]).parent_path();
   fs::current_path(path);
   std::cout<<argv[0]<<endl;
   //LevelObject::registerType(LevelObjects::TypeKeeper,&Keeper::instance);
   //LevelObject::registerType(LevelObjects::TypeWall,&Wall::instance);
   //LevelObject::registerType(LevelObjects::TypeBox,&Box::instance);
   SDLEngine e_sdl;
   cout<<"SDL engine allocated!"<<endl;
   CursesEngine e_curs;
   cout<<"curses engine allocated!"<<endl;
   GameEngine *e;
   SokobanLogic sokoban;
   cout<<"logic engine allocated!"<<endl;
   Keeper *k=new Keeper;
   delete k;
   if(argc<=1&&getConsole())
        e=&e_curs;
   else
        e=&e_sdl;
   sokoban.setEngine(e);
   sokoban.Main();
   return 0;
}

