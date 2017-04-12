#define ENEMY_WIDTH 12
#define NUM_ENEMIES 35

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
    GW->lEnemy = 0;
    GW->rEnemy = 34;
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
    if(GW->E[GW->lEnemy]) return;
    int i;
    for(i = GW->lEnemy; i < NUM_ENEMIES; i++)
        if(GW->E[i]) break;
    GW->lEnemy = i;
}

// Checks rightmost enemy index and updates if necessary
void checkRightBound(GameWindow* GW){
    if(GW->E[GW->rEnemy]) return;
    int i;
    for(i = GW->rEnemy; i >= 0; i--)
        if(GW->E[i]) break;
    GW->lEnemy = i;
}

int getBlockWidth(int lInd, int rInd){
    int lCol = lInd/5;
    int rCol = rInd/5;
    return rCol-lCol+1;
}

// Checks if shift is allowable and updates direction if not
bool checkShiftDir(GameWindow* GW){
    int blockWidth = getBlockWidth(GW->lEnemy,GW->rEnemy);
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

