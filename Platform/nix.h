#pragma once
#include <cstring>
bool getConsole(){
    if(!getenv("TERM")||!strlen(getenv("TERM")))
        return false;
    else return true;
}
