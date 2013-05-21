#include "SDLEngine.h"
SDLEngine::SDLEngine(){
} 
SDL_Surface *SDLEngine::Load(const char *file){
    SDL_Surface *temp,*res;
    temp=SDL_LoadBMP(file);
    res=SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    return res;
}
void SDLEngine::Init(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_EnableUNICODE(1);
    screen=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    empty=Load("empty.bmp");
    keeper=Load("keeper.bmp");
    SDL_SetColorKey(keeper,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,255,255,255));
    box=Load("box.bmp");
    SDL_SetColorKey(box,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,255,255,255));
    mark=Load("mark.bmp");
    //SDL_SetColorKey(mark,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,255,255,255));
    wall=Load("wall.bmp");
    SDL_SetColorKey(wall,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,255,255,255));
    boxm=Load("boxm.bmp");
    SDL_SetColorKey(boxm,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,255,255,255));
    cursor=Load("cursor.bmp");
    SDL_SetColorKey(cursor,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,255,255,255));
    font=TTF_OpenFont("opensans.ttf",16);
}

void SDLEngine::Stop(){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_FreeSurface(empty);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(keeper);
    SDL_FreeSurface(box);
    SDL_FreeSurface(mark);
    SDL_FreeSurface(boxm);
    SDL_Quit();
}

SDLEngine::~SDLEngine(){
}

Keys SDLEngine::getKey(){
    SDL_Event event;
    a:SDL_WaitEvent(&event);
    if(modeRawInput
       &&event.type==SDL_KEYDOWN
       &&!(event.key.keysym.unicode & 0xFF80)){
            rawInput=event.key.keysym.unicode;
            return CONTROL_RAWINPUT;
    }
    if(event.type!=SDL_KEYDOWN){
        if(event.type==SDL_QUIT)
            exit(0);
            //logic_->stop();
        goto a;
        return KEY_NONE;
    }
    SDL_keysym key=event.key.keysym;
    switch(key.sym){
    case SDLK_a:
    case SDLK_LEFT:
        return MOVE_LEFT;
        break;
    case SDLK_w:
    case SDLK_UP:
        return MOVE_UP;
        break;
    case SDLK_s:
    case SDLK_DOWN:
        return MOVE_DOWN;
        break;
    case SDLK_d:
    case SDLK_RIGHT:
        return MOVE_RIGHT;
        break;
    case SDLK_1:
        return OPTION_1;
        break;
    case SDLK_2:
        return OPTION_2;
        break;
    case SDLK_3:
        return OPTION_3;
        break;
    case SDLK_4:
        return OPTION_4;
        break;
    case SDLK_DELETE:
    case SDLK_BACKSPACE:
        return CONTROL_DELETE;
        break;
    case SDLK_F2:
        return CONTROL_SAVE;
        break;
    case SDLK_q:
    case SDLK_ESCAPE:
        return CONTROL_CANCEL;
        break;
    default:
        goto a;
        return KEY_NONE;
    };
}
void SDLEngine::showMenu(Menu* m){
    SDL_FillRect(screen,NULL,0);
    int y,x;
    y=0;
    SDL_Surface *temp;
    SDL_Rect rect;
    SDL_Color inactive={255,255,255},
              active={255,0,0},
              current_color;
    int size=m->size();
    for(int i=0;i<size;i++){
        MenuElem* ptr=m->element(i);
        if(!ptr->visible)
            continue;
        if(ptr->text.size()){
            if(ptr==m->current())
                temp=TTF_RenderUTF8_Blended(font,ptr->text.c_str(),active);
            else 
                temp=TTF_RenderUTF8_Blended(font,ptr->text.c_str(),inactive);
        } else
            temp=TTF_RenderUTF8_Blended(font," ",active);
        rect.x=(screen->w-temp->w)/2;
        rect.y=y;
        SDL_BlitSurface(temp,NULL,screen,&rect);
        y+=temp->h+10;
        SDL_FreeSurface(temp);
    }
    SDL_Flip(screen);
}
void SDLEngine::showLevel(Level *level){
    SDL_Rect rect={0,0,0,0};
    int m,n;
    level->getSize(n,m);
    for(int i=0;i<n;i++){
        rect.x=0;
        for(int j=0;j<m;j++){
            if (level->isMarked(i,j))
                SDL_BlitSurface(mark,NULL,screen,&rect);
            else 
                SDL_BlitSurface(empty,NULL,screen,&rect);
            LevelObject *o=level->getObject(i,j);
            if(o){
                std::cout<<o<<std::endl;
                std::string type=o->type_name();
                if(type=="Keeper")
                        SDL_BlitSurface(keeper,NULL,screen,&rect);
                else if(type=="Box"){
                    if (level->isMarked(i,j))
                        SDL_BlitSurface(boxm,NULL,screen,&rect);
                    else 
                        SDL_BlitSurface(box,NULL,screen,&rect);
                } else if(type=="Wall")
                        SDL_BlitSurface(wall,NULL,screen,&rect);
                else;
                        //SDL_BlitSurface(empty,NULL,screen,&rect);
            }
            rect.x+=32;
        }
        rect.y+=32;
    }
}

void SDLEngine::showLevelScreen(LevelScreen *ls){
    SDL_FillRect(screen,NULL,0);
    showLevel(ls->level);
    SDL_Flip(screen);
};
void SDLEngine::showEditor(Editor *e){
    SDL_FillRect(screen,NULL,0);
    SDL_Rect rect={0,0,0,0};
    Cursor *c=e->cursor;    
    showLevel(e->level());
    rect.x=c->x*32;
    rect.y=c->y*32;
    SDL_BlitSurface(cursor,NULL,screen,&rect);
    SDL_Flip(screen);
};
void SDLEngine::showSizeEditor(){};
void SDLEngine::showWin(WinScreen *w){
    SDL_FillRect(screen,NULL,0);
    int y,x;
    y=0;
    SDL_Color inactive={255,255,255},
              active={255,0,0},
              current_color;
    SDL_Surface *temp;
    SDL_Rect rect;
    temp=TTF_RenderUTF8_Blended(font,w->caption.c_str(),active);
    rect.x=(screen->w-temp->w)/2;
    rect.y=y;
    SDL_BlitSurface(temp,NULL,screen,&rect);
    SDL_FreeSurface(temp);
    y+=temp->h+10;
    temp=TTF_RenderUTF8_Blended(font,w->text.c_str(),inactive);
    rect.x=(screen->w-temp->w)/2;
    rect.y=y;
    SDL_BlitSurface(temp,NULL,screen,&rect);
    SDL_FreeSurface(temp);
    y+=temp->h+10;
    SDL_Flip(screen);
};
void SDLEngine::showLose(){};
char SDLEngine::getRawInput(){return rawInput;};
