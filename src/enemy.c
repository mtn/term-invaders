#define ENEMY_WIDTH 12

#include <stdlib.h>

#include "lib/main.h"
#include "lib/enemy.h"

EnemyLL* initializeEnemies(GameWindow* GW){
    EnemyLL* enemyLL = malloc(sizeof(EnemyLL));
    enemyLL->prev = NULL;
    enemyLL->next = NULL;
    EnemyLL* first = enemyLL;

    for(int i = 0; i < 55; ++i){
        Enemy *E = malloc(sizeof(Enemy));
        E-> isAlive = true;

        if(i <= 11) E->img = GW->farEnemy;
        else if(i <= 33) E->img = GW->midEnemy;
        else E->img = GW->nearEnemy;

        enemyLL->E = E;
        enemyLL->next->prev = enemyLL;
        enemyLL = enemyLL->next;
    }

    return first;
}

void renderEnemies(GameWindow* GW){
    EnemyLL* e = GW->ELL;
    for(int i = 0; i < 55; ++i){
        if(i <= 11) renderFar(GW,i);
        else if(i <= 33) renderMedium(GW,i);
        else renderNear(GW,i);
    }
    wrefresh(GW->W);
}

void clearEnemies(GameWindow* GW){
    int locx, locy;
    Coord *c;
    // Clear each of the 5 rows
    for(int i = 0; i < 55; i+=11){

        wmove(GW->W,locy, 0);
        wclrtoeol(GW->W);
        wmove(GW->W,locy+1, 0);
        wclrtoeol(GW->W);
        wmove(GW->W,locy+2, 0);
        wclrtoeol(GW->W);


        free(c);
    }
    // Box gets ruined
    box(GW->W,0,0);
    wrefresh(GW->W);
}

// The core enemies (except unimplemented UFO) move as a block
void shiftEnemiesLeft(GameWindow* GW){
    clearEnemies(GW);

    if(GW->enemyHorizLoc > 0)
        --GW->enemyHorizLoc;
}

void shiftEnemiesRight(GameWindow* GW){
    clearEnemies(GW);
    if(GW->enemyVertLoc < GW->enemyHorizBound)
        ++GW->enemyHorizLoc;
}

