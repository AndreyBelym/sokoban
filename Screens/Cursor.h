#pragma once
#include "../Level/Level.h"
#include <iostream>
struct Cursor{
   int x,y;
   Level *level;
   Cursor():x(0),y(0){};
   void move(int dx,int dy){
       x+=dx;y+=dy;
       int rows,cols;
       level->getSize(rows,cols);
       if(x<0){
           x+=cols;
       }
       if(x>=cols){
           x-=cols;
       }
       if(y<0){
           y+=rows;
       }
       if(y>=rows){
           y-=rows;
       }
       std::cout<<x<<" "<<y<<std::endl;
   }
   void moveLeft(){move(-1,0);}
   void moveRight(){move(1,0);}
   void moveUp(){move(0,-1);}
   void moveDown(){move(0,1);}
}; 
