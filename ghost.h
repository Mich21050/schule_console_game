//
// Created by Huawei on 11/01/2023.
//
#include "Bauer.h"
#ifndef GAME_GHOST_H
#define GAME_GHOST_H

class Ghost : public Bauer
{
protected:
    int  armor;		// reduces the damage Heros gets
    char block;		// is blocking active?
private:
    void printTwo(int xoff,int yoff, int count){
        for(int i = 0; i < std::abs(count);i++){
            if(count < 0)
                Linie(xoff,yoff-i,1,0,bodyC);
            else
                Linie(xoff,yoff+i,1,0,bodyC);
        }
    }
    void ShowGhost(int offset){
        setcolor(bodyCol);
        Linie((x+offset) - 5, height, 9, 0, bodyC);
        Linie((x+offset) - 9, height - 1, 3, 0, bodyC);
        Linie((x+offset) - 11, height - 2, 1, 0, bodyC);
        printTwo((x+offset)-13,height-3,-2);
        printTwo((x+offset)-15,height-5,-6);
        printTwo((x+offset)-13,height-11,-2);
        Linie((x+offset)-11,height-13,1,0,bodyC);
        Linie((x+offset)-9,height-14,3,0,bodyC);
        Linie((x+offset)-5, height-15,11,0,bodyC);
        Linie((x+offset)+7,height-14,3,0,bodyC);
        Linie((x+offset)+11,height-13,1,0,bodyC);
        Linie((x+offset)+13,height-12,1,0,bodyC);
        printTwo((x+offset)+15,height-11,4);
        Linie((x+offset)+13, height-7,1,0,bodyC);
        printTwo((x+offset)+15,height-6,2);
        Linie((x+offset)+13,height-4,1,0,bodyC);
        Linie((x+offset)+11,height-3,1,0,bodyC);
        Linie((x+offset)+9,height-2,1,0,bodyC);
        Linie((x+offset)+5,height-1,3,0,bodyC);
        setcolor(headCol);
        printTwo((x+offset)-5,height-4,-2);
        printTwo((x+offset)-9,height-4,-2);
        printTwo((x+offset)+9,height-5,-3);
        Linie((x+offset)+5,height-5,3,0,bodyC);
        Linie((x+offset)+3,height-6,1,0,bodyC);
        Linie((x+offset)+7,height-8,1,0,bodyC);

        Linie((x+offset)-11,height-8,1,0,bodyC);
        Linie((x+offset)-1,height-8,1,0,bodyC);

        Linie((x+offset)-9,height-9,7,0,bodyC);

    }
public:
    Ghost()
    {
        strcpy(autorName, "Wannninger");
        strcpy(heroName, "Ghost");

        life       = MAX_LIFE;
        damage     = STD_DAMAGE;
        armor      = STD_DAMAGE/4;
        range      = 14;
        mana       = MAX_MANA/10*3;
        move       = MAX_MOVE/2+1;
        block      = 0;

        headCol    = WHITE;
        bodyCol = WHITE;
        bodyC = 219;
    }

    /**/
    void ShowMan() {
        ShowGhost(0);

    }
    void SetBodyC(char zeichen) {bodyC = zeichen;}
    void ShowWeapon(){

    }
    void ShowStart(){
        Clear();
        x= MIDDLE;
        ShowMan();
    }
};

#endif //GAME_GHOST_H
