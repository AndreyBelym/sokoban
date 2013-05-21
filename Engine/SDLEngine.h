#pragma once
#include "../Engine/BaseGameEngine.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
class SDLEngine:public BaseGameEngine{
  private:
    SDL_Surface *screen,
                *empty,
                *keeper,
                *box,
                *boxm,
                *mark,
                *cursor,
                *wall;
    TTF_Font *font;
  public:
    SDLEngine();   
    ~SDLEngine();
    void Init();
    void Stop();
    SDL_Surface *Load(const char*);
    Keys getKey();
    void showMenu(Menu* m);
    void showLevel(Level *l);
    void showLevelScreen(LevelScreen *l);
    void showEditor(Editor *l);
    void showSizeEditor();
    void showWin(WinScreen *w);
    void showLose();
    char getRawInput();
} ; 
