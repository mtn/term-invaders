#include <stdlib.h>

#include "lib/main.h"
#include "lib/enemy.h"

// 11 columns of enemies,
void initializeEnemies(GameWindow* GW){
    Enemy **enemies = calloc(55,sizeof(Enemy*));
    for(int i = 0; i < 55; ++i){
        Enemy *e = calloc(1,sizeof(Enemy));
        e-> isAlive = true;

        if(i <= 11) e->type = FAR;
        else if(i <= 33) e->type = MEDIUM;
        else e->type = NEAR;

        Coord *C = calloc(1,sizeof(Coord));
        C->x = (i%11) << 1;
        C->y = (i/11) + 3;
        e->loc = C;
        enemies[i] = e;
    }
    GW->E = (void**)enemies;
}

void renderEnemies(GameWindow* GW){
    for(int i = 0; i < 55; ++i){
        if(((Enemy**)GW->E)[i]->isAlive){
            wmvaddch(GW->W,((Enemy**)GW->E)[i]->loc->y,((Enemy**)GW->E)[i]->loc->x,'@');
        }
    }
}

void shiftLeft(GameWindow* GW){

}

void shiftRight(GameWindow* GW){

}

