#include "CursesEngine.h"
CursesEngine::CursesEngine(){
}

CursesEngine::~CursesEngine(){    
}

void CursesEngine::Init(){
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    getmaxyx(stdscr,term_rows,term_cols);
    clear();
}

void CursesEngine::Stop(){
    endwin();
}

Keys CursesEngine::getKey(){
        a:
        int key=getch();
        if(modeRawInput){
                key=(key==KEY_BACKSPACE||key==KEY_DC?'\b':key);
                rawInput=key;
                return CONTROL_RAWINPUT;
       }
        switch(key){
        case 'a':
        case KEY_LEFT:
            return MOVE_LEFT;
            break;
        case 'w':
        case KEY_UP:
            return MOVE_UP;
            break;
        case 's':
        case KEY_DOWN:
            return MOVE_DOWN;
            break;
        case 'd':
        case KEY_RIGHT:
            return MOVE_RIGHT;
            break;
        case '1':
            return OPTION_1;
            break;
        case '2':
            return OPTION_2;
            break;
        case '3':
            return OPTION_3;
            break;
        case '4':
            return OPTION_4;
            break;
        case KEY_DC:
        case KEY_BACKSPACE:
            return CONTROL_DELETE;
            break;
        case 'S':
            return CONTROL_SAVE;
            break;
        case 'Q':
        case 27:
            return CONTROL_CANCEL;
            break;
        default:
            
            goto a;
            return KEY_NONE;
    };
}
void CursesEngine::showMenu(Menu* m){
    clear();
    int crow,cccol;
    int size=m->size();
    crow=0;
    for(int i=0;i<size;i++){
        MenuElem* ptr=m->element(i);
        if (!ptr->visible)
            continue;
        move(crow,(term_cols-ptr->text.size())/2);
        if(ptr==m->current())
            printw("||%s||",ptr->text.c_str());
        else
            printw("  %s  ",ptr->text.c_str());
        crow++;
    }
    refresh();
};
void CursesEngine::showLevel(Level *level){
    int m,n;
    level->getSize(n,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            LevelObject *o=level->getObject(i,j);
            if(o){
                std::string type=o->type_name();
                if(type=="Keeper")
                    addch('@');
                else if(type=="Box")
                    if(level->isMarked(i,j))
                        addch('0');
                    else
                        addch('o');
                else if(type=="Wall")
                    addch('#');
                else
                    addch('.');
            }
            else if (level->isMarked(i,j))
                addch('x');
            else addch('.');
        }
        addch('\n');
    }
}
void CursesEngine::showLevelScreen(LevelScreen *ls){
    clear();
    move(0,0);
    Level *level=ls->level;
    showLevel(level);
    refresh();
}
void CursesEngine::showEditor(Editor *e){
    clear();
    move(0,0);
    Level *level=e->level();
    Cursor *c=e->cursor;
    showLevel(level);
    move(c->y,c->x);
    addch('V');
    refresh();
}
void CursesEngine::showSizeEditor(){};
void CursesEngine::showWin(WinScreen *w){
    clear();
    move(term_rows/2,(term_cols-w->caption.size())/2);
    printw(w->caption.c_str());
    move(term_rows/2+1,(term_cols-w->text.size())/2);
    printw(w->text.c_str());
    refresh();
};
void CursesEngine::showLose(){};
char CursesEngine::getRawInput(){
    return rawInput;
}
