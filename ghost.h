//
// Created by Huawei on 11/01/2023.
//
#include "Bauer.h"
#include "windows.h"
#include "sys/stat.h"
#pragma comment(lib, "urlmon.lib")

#ifndef GAME_GHOST_H
#define GAME_GHOST_H
#include "stdlib.h"
#define animation 3

class Ghost : public Bauer
{
protected:
    int  armor;		// reduces the damage Heros gets
    char block;		// is blocking active?
    bool isInvisible;
private:
    void printTwo(int xoff,int yoff, int count){
        for(int i = 0; i < std::abs(count);i++){
            if(count < 0)
                Linie(xoff,yoff-i,1,0,bodyC);
            else
                Linie(xoff,yoff+i,1,0,bodyC);
        }
    }
    void ShowGhost(){
        setcolor(bodyCol);
        Linie(x - 5, height, 9, 0, bodyC);
        Linie(x - 9, height - 1, 3, 0, bodyC);
        Linie(x - 11, height - 2, 1, 0, bodyC);
        printTwo(x-13,height-3,-2);
        printTwo(x-15,height-5,-6);
        printTwo(x-13,height-11,-2);
        Linie(x-11,height-13,1,0,bodyC);
        Linie(x-9,height-14,3,0,bodyC);
        Linie(x-5, height-15,11,0,bodyC);
        Linie(x+7,height-14,3,0,bodyC);
        Linie(x+11,height-13,1,0,bodyC);
        Linie(x+13,height-12,1,0,bodyC);
        printTwo(x+15,height-11,4);
        Linie(x+13, height-7,1,0,bodyC);
        printTwo(x+15,height-6,2);
        Linie(x+13,height-4,1,0,bodyC);
        Linie(x+11,height-3,1,0,bodyC);
        Linie(x+9,height-2,1,0,bodyC);
        Linie(x+5,height-1,3,0,bodyC);
        setcolor(headCol);
        printTwo(x-5,height-4,-2);
        printTwo(x-9,height-4,-2);
        printTwo(x+9,height-5,-3);
        Linie(x+5,height-5,3,0,bodyC);
        Linie(x+3,height-6,1,0,bodyC);
        Linie(x+7,height-8,1,0,bodyC);

    }
    void showNormalMouth(){
        //mouth
        Linie(x-11,height-8,1,0,bodyC);
        Linie(x-1,height-8,1,0,bodyC);
        Linie(x-9,height-9,7,0,bodyC);
    }
    void ShowAttackMouth(){
        Linie(x-8,height-8,3,0,bodyC);
        Linie(x-8,height-11,3,0,bodyC);
        printTwo(x-10,height-9,-2);
        printTwo(x-4,height-9,-2);
    }
    void ShowSadMouth(){
        Linie(x-11,height-10,1,0,bodyC);
        Linie(x-1,height-10,1,0,bodyC);
        Linie(x-9,height-9,7,0,bodyC);
    }
    void ClearSadMouth(){
        int oldbodyC = bodyC;
        bodyC = ' ';
        ShowSadMouth();
        bodyC = oldbodyC;
    }
    void ClearText(int x, int y, int len){
        Text(x,y,string(len, ' ').c_str());
    }
    void MoveUpDown(int wohin, int style){
        // move = speed = range of movement
        if(wohin > +move) wohin = +move;
        if(wohin < -move) wohin = -move;

        // positiv wohin => ZUR MITTE
        for(int i=0; i<wohin; i++)
        {
            if( x<=-MIDDLE+width ) break;
            if( x + enemy->x <= MIN_DISTANCE
                                + width + enemy->width ) break;
            Clear();
            x--;                // Move Fighter
            if(style == 0) {
                if (i % 5 == 0) {
                    height--;
                }
            } else if(style == 1){
                if(height == 25)
                    height=23;
                else if(height == 23)
                    height=25;
            } else if(style == 2){
                if(height == 23)
                    height=25;
                else if(height == 25)
                    height=23;
            }
            step = (step+1)%3;
            Show();
            Sleep(SLEEP_MOVE);
        }
        Clear();
        step = 2;
        Show();
    }
    void Attack(int damageIn){
        damage = 0;
        Clear();
        ShowGhost();
        ShowAttackMouth();
        setcolor(RED);
        int distTee = enemy->x+enemy->width;

        int yoff = 0;
        for(int i = 0; i < range; i++){
            if(GetKeyState(VK_UP) & 0x8000)
                yoff += 1;
            else if(GetKeyState(VK_DOWN) & 0x8000)
                yoff -= 1;
            setcolor(RED);
            Linie(x-20-i,height-9+yoff,3,0,219);
            Linie(x-20-i,height-10+yoff,3,0,219);
            Sleep(50);
            Linie(x - 20 - i, height - 9 + yoff, 3, 0, 32);
            Linie(x - 20 - i, height - 10 + yoff, 3, 0, 32);
            if((i > enemy->x+(x-width)) && ((height-10+yoff) < enemy->height)){
                damage = damageIn;
                break;
            }
        }
        Clear();
        ShowGhost();
        showNormalMouth();
    }
    void downloadSound(string name){
        string dwnld_URL = "https://github.com/Mich21050/schule_console_game/raw/master/soundSource/"+name;
        string path = "SoundEffects/"+name;
        URLDownloadToFile(NULL, dwnld_URL.c_str(), path.c_str(), 0, NULL);
    }
    bool fileExists(string name){
        struct stat buffer;
        return (stat (name.c_str(), &buffer) == 0);
    }
public:
    Ghost()
    {
        strcpy(autorName, "Wanninger");
        strcpy(heroName, "Ghost");

        life       = 45;
        damage     = STD_DAMAGE;
        armor      = STD_DAMAGE/4;
        range      = 80;
        mana       = 45;
        move       = MAX_MOVE/2+1;
        block      = 0;
        height = 25;
        width = 18;
        hand = 0;
        leg = 0;

        isInvisible = false;

        headCol    = WHITE;
        bodyCol = WHITE;
        bodyC = 219;
        weaponC    = ' ';
        armorC     = ' ';
        handCol    = BLACK;
        legCol     = BLACK;
        weaponCol  = BLACK;
        string sounds[2] ={"ghost_laugh.wav","ghost_death.wav"};
        for(string tmp:sounds){
            if(!fileExists("SoundEffects/"+tmp))
                downloadSound(tmp);

        }
    }

    /**/
    void ShowMan() {
        ShowGhost();
        showNormalMouth();

    }
    void ShowWeapon(){

    }
    void ShowWeapon(int dx, int dy, char zeichen)
    {
    }
    void ShowStart(){
        int oldX = x;
        int oldMove = move;
        move=WIDTH;
        x = 80;


        if(animation == 0) {
            height += 10;
            MoveUpDown(x - oldX, 0);
        } else if(animation == 1){
            MoveUpDown(x-oldX, 1);
        } else if(animation == 2){
            height = 23;
            int goal = x -oldX;
            Move(goal/2);
            MoveUpDown(goal/2, 2);
        } else if(animation == 3){
            x = oldX;
            ShowMan();
        }


        move = oldMove;
        Text(x+3,height-17,"Bei Angriff Feuerball mit Pfeiltasten steuern");
        Sleep(3000);
        ClearText(x+3,height-17,45);
    }
    void ShowAttack(){
        Attack(STD_DAMAGE);
    }
    void Clear()
    {
        char saveBody   = bodyC;
        char saveWeapon = weaponC;
        char saveArmor  = armorC;
        bodyC   = ' ';
        weaponC = ' ';
        armorC  = ' ';
        ShowGhost();
        ShowAttackMouth();
        showNormalMouth();
        bodyC   = saveBody;
        weaponC = saveWeapon;
        armorC  = saveArmor;
    }
    void Magic(){
        Text(x+4,height-17,"u ^ unsichtbar/kein Schaden [25 Mana]");
        Text(x+4,height-18,"f ^ Feuerball/doppelter Schaden [20 Mana]");
        char sel = tolower(getch());
        if(sel == 'u'){
            isInvisible = true;
            Clear();
            bodyC = 176;
            ShowMan();
            mana -= 25;
            ShowLife();
        }
        else if(sel == 'f'){
            mana -= 20;
            ShowLife();
            enemy->ShowBlock();
            Attack(STD_DAMAGE*2);
            enemy->BeAttacked();
            enemy->ClearBlock();
            enemy->Show();
        }
        ClearText(x+4,height-17,37);
        ClearText(x+4,height-18,41);
    }
    int BeAttacked(){
        int damage = enemy->DoAttack();
        if(!isInvisible) {
            life -= damage;
            ShowLife();
            return damage;
        }
        else if(damage != 0){
            isInvisible = false;
            Clear();
            bodyC =219;
            ShowMan();
            return 0;
        }
        else
            return 0;

    }
    void ShowDeath(){
        if(life>0) return;
        PlaySound("SoundEffects/ghost_death.wav", NULL, SND_FILENAME | SND_ASYNC);
        Clear();
        bodyC = 179;
        int oldH = height;
        for(int i = 0; i < oldH;i++){
            height -= i;
            ShowGhost();
            ShowSadMouth();
            Sleep(200);
            Clear();
            ClearSadMouth();
        }
    }
    void ShowVictory(){
        Text(x-20,height-8,"Gotcha");
        PlaySound("SoundEffects/ghost_laugh.wav", NULL, SND_FILENAME | SND_ASYNC);
        for(int i = 0; i < 16;i++){
            Clear();
            if(height == 25)
                height = 23;
            else if(height == 23)
                height = 25;
            ShowMan();
            Sleep(50);
        }


    }
};

#endif //GAME_GHOST_H
