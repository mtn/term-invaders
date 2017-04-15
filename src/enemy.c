#define ENEMY_WIDTH  7
#define NUM_ENEMIES 35
#define NUM_COLS     7

#include <stdlib.h>

#include "lib/main.h"
#include "lib/enemy.h"

void initializeEnemies(GameWindow* GW){
    Enemy** enemies = malloc(NUM_ENEMIES*sizeof(Enemy*));

    // Approx. half the screen occupied at at time
    int horizOffset = (int)((GW->boundX)/15);
    int vertOffset = 6;
    for(int i = 0; i < 35; ++i){
        Enemy *E = malloc(sizeof(Enemy));
        Coord *loc = malloc(sizeof(Coord));

        loc->x = (i / 5) * horizOffset + 1;
        loc->y = (i % 5) * vertOffset + 2;
        E->loc = loc;

        if(i % 5 == 0){
            E->img1 = GW->images->farEnemy1;
            E->img2 = GW->images->farEnemy2;
        }
        else if(i % 5 == 1 || i % 5 == 2){
            E->img1 = GW->images->midEnemy1;
            E->img2 = GW->images->midEnemy2;
        }
        else{
            E->img1 = GW->images->nearEnemy1;
            E->img2 = GW->images->nearEnemy2;
        }

        enemies[i] = E;
    }

    GW->enemyHorizOffset = horizOffset;
    GW->enemyVertOffset = horizOffset;
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

bool moveEnemyBlockDown(GameWindow* GW){
    for(int i = 0; i < NUM_ENEMIES; i++){
        derenderImg(GW,GW->E[i]->img1,GW->E[i]->loc->y,GW->E[i]->loc->x);
        ++GW->E[i]->loc->y;
        if(GW->E[i]->loc->y > GW->boundY - 8) return false;
    }
    return true;
}

void moveEnemyBlockLeft(GameWindow* GW){
    for(int i = 0; i < NUM_ENEMIES; i++){
        if(GW->E[i]){
            derenderImg(GW,GW->E[i]->img1,GW->E[i]->loc->y,GW->E[i]->loc->x);
            --GW->E[i]->loc->x;
            if(GW->E[i]->loc->x == 1 && GW->shiftDir == LEFT){
                GW->shiftDir = RIGHT;
                moveEnemyBlockDown(GW);
            }
       }
    }
    wrefresh(GW->W);
}

void moveEnemyBlockRight(GameWindow* GW){
    for(int i = 0; i < NUM_ENEMIES; i++){
        if(GW->E[i]){
            derenderImg(GW,GW->E[i]->img1,GW->E[i]->loc->y,GW->E[i]->loc->x);
            ++GW->E[i]->loc->x;
            if(GW->E[i]->loc->x == GW->boundX - ENEMY_WIDTH){
                GW->shiftDir = LEFT;
            }
       }
    }
    wrefresh(GW->W);
}

