#define ENEMY_WIDTH 12
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

    GW->shiftCount = 0;
    GW->enemyHorizOffset = horizOffset;
    GW->enemyVertOffset = horizOffset;
    GW->enemyCol = malloc(NUM_COLS*sizeof(int));
    for(int i = 0; i < NUM_COLS; i++) GW->enemyCol[i] = NUM_ENEMIES/NUM_COLS;
    GW->lEnemyCol = 0;
    GW->rEnemyCol = NUM_COLS-1;
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

// Checks leftmost enemy index and updates if necessary
void checkLeftBound(GameWindow* GW){
    if(GW->enemyCol[GW->lEnemyCol]) return;
    int i;
    for(i = GW->lEnemyCol; i <= NUM_COLS; i++)
        if(GW->enemyCol[i]) break;
    GW->lEnemyCol = i;
}

// Checks rightmost enemy index and updates if necessary
void checkRightBound(GameWindow* GW){
    if(GW->enemyCol[GW->rEnemyCol]) return;
    int i;
    for(i = GW->rEnemyCol; i >= 0; i--)
        if(GW->enemyCol[i]) break;
    GW->lEnemyCol = i;
}

int getBlockWidth(int lCol, int rCol){
    return rCol-lCol+1;
}

// Checks if shift is allowable and updates direction if not
bool checkShiftDir(GameWindow* GW){
    int blockWidth = getBlockWidth(GW->lEnemyCol,GW->rEnemyCol);
    switch(GW->shiftDir){
        case LEFT:
            checkLeftBound(GW);
            if(GW->shiftCount + (7-blockWidth) * GW->enemyHorizOffset > 0) return true;
            else{
                if(!moveEnemyBlockDown(GW)) return false;
                GW->shiftDir = !GW->shiftDir;
            }
            break;
        case RIGHT:
            checkRightBound(GW);
            if(GW->shiftCount < GW->boundX-(blockWidth*GW->enemyHorizOffset)+4) return true;
            else GW->shiftDir = !GW->shiftDir;
            break;
    }
    return true;
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
    --GW->shiftCount;
    for(int i = 0; i < NUM_ENEMIES; i++){
        if(GW->E[i]){
            derenderImg(GW,GW->E[i]->img1,GW->E[i]->loc->y,GW->E[i]->loc->x);
            --GW->E[i]->loc->x;
       }
    }
    wrefresh(GW->W);
}

void moveEnemyBlockRight(GameWindow* GW){
    ++GW->shiftCount;
    for(int i = 0; i < NUM_ENEMIES; i++){
        if(GW->E[i]){
            derenderImg(GW,GW->E[i]->img1,GW->E[i]->loc->y,GW->E[i]->loc->x);
            ++GW->E[i]->loc->x;
       }
    }
    wrefresh(GW->W);
}

