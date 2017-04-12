#define ENEMY_WIDTH 12
#define NUM_ENEMIES 35

#include <stdlib.h>

#include "lib/main.h"
#include "lib/enemy.h"

void initializeEnemies(GameWindow* GW){
    Enemy** enemies = malloc(NUM_ENEMIES*sizeof(Enemy*));

    // Approx. half the screen occupied at at time
    int horizOffset = (int)((GW->boundX)/15);
    for(int i = 0; i < 35; ++i){
        Enemy *E = malloc(sizeof(Enemy));
        Coord *loc = malloc(sizeof(Coord));

        E->isAlive = true;

        loc->x = (i % 7) * horizOffset + 1;
        loc->y = (i / 7) * 6 + 2;
        E->loc = loc;

        if(i < 7){
            E->img1 = GW->images->farEnemy1;
            E->img2 = GW->images->farEnemy2;
        }
        else if(i < 21){
            E->img1 = GW->images->midEnemy1;
            E->img2 = GW->images->midEnemy2;
        }
        else{
            E->img1 = GW->images->nearEnemy1;
            E->img2 = GW->images->nearEnemy2;
        }

        enemies[i] = E;
    }

    GW->E = enemies;
}

void renderEnemies(GameWindow* GW){
    for(int i = 0; i < NUM_ENEMIES; i++)
        if(GW->state)
            renderImg(GW,GW->E[i]->img1,GW->E[i]->loc->y,GW->E[i]->loc->x);
        else
            renderImg(GW,GW->E[i]->img2,GW->E[i]->loc->y,GW->E[i]->loc->x);
}

void derenderEnemies(GameWindow* GW){
    for(int i = 0; i < NUM_ENEMIES; i++)
        if(GW->state)
            derenderImg(GW,GW->E[i]->img1,GW->E[i]->loc->y,GW->E[i]->loc->x);
        else
            derenderImg(GW,GW->E[i]->img2,GW->E[i]->loc->y,GW->E[i]->loc->x);
}

int getBlockWidth(GameWindow* GW){
    int i;
    for(i = 7; i > 0; i--)
        if(GW->colCount[i]) break;
    return i;
}

void moveEnemyBlockLeft(GameWindow* GW){
    int width = getBlockWidth(GW);
    if(E->loc->x > 1){
        derenderImg(GW,E->img1,E->loc->y,E->loc->x);
        --E->loc->x;
    }
    wrefresh(GW->W);
}

void moveEnemyBlockRight(GameWindow* GW){
    int width = getBlockWidth(GW);
    if(E->loc->x > 1){
    if(E->loc->x < (GW->boundX - E->img1->xDim)){
        derenderImg(GW,E->img1,E->loc->y,E->loc->x);
        --E->loc->x;
    }
    wrefresh(GW->W);
}

