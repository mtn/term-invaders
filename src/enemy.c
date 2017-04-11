#define ENEMY_WIDTH 12

#include <stdlib.h>

#include "lib/main.h"
#include "lib/enemy.h"

void initializeEnemies(GameWindow* GW){
    EnemyLL* enemyLL = malloc(sizeof(EnemyLL));
    enemyLL->prev = NULL;
    enemyLL->next = NULL;
    EnemyLL* first = enemyLL;

    for(int i = 0; i < 55; ++i){
        Enemy *E = malloc(sizeof(Enemy));
        E->isAlive = true;

        if(i <= 11){
            E->img1 = GW->images->farEnemy1;
            E->img2 = GW->images->farEnemy2;
        }
        else if(i <= 33){
            E->img1 = GW->images->midEnemy1;
            E->img2 = GW->images->midEnemy2;
        }
        else{
            E->img1 = GW->images->nearEnemy1;
            E->img2 = GW->images->nearEnemy2;
        }

        enemyLL->E = E;
        EnemyLL* nextLink = malloc(sizeof(EnemyLL));
        nextLink->prev = enemyLL;
        nextLink->next = NULL;
        enemyLL->next = nextLink;
        enemyLL = enemyLL->next;
    }

    GW->ELL = first;
}

void moveEnemyLeft(GameWindow* GW, Enemy* E){
    if(E->loc->x > 1){
        derenderImg(GW,E->img1,E->loc->y,E->loc->x);
        --E->loc->x;
    }
    wrefresh(GW->W);
}

void moveEnemyRight(GameWindow* GW, Enemy* E){
    if(E->loc->x < (GW->boundX - E->img1->xDim)){
        derenderImg(GW,E->img1,E->loc->y,E->loc->x);
        --E->loc->x;
    }
    wrefresh(GW->W);
}

