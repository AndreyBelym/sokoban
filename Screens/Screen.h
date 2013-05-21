#pragma once
#include "../Engine/Keys.h"
class Screen{
    public:
        enum Types{MENU,LEVELSCREEN,EDITOR,WIN_SCREEN} type;
        virtual int DispatchKey(const Keys &key)=0;
        virtual ~Screen(){};
};
