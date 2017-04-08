#include <stdlib.h>

#include "lib/enemy.h"

// 11 columns of enemies,
void addEnemies(GameWindow* GW){
    Enemy *enemies = calloc(55,sizeof(Enemy));
    for(int i = 0; i < 55; ++i){
        enemies->isAlive = true;
    }
}

void shiftLeft(GameWindow* GW){

}

void shiftRight(GameWindow* GW){

}

