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
        Coord *loc = malloc(sizeof(Coord));

        E->isAlive = true;
        loc->x = (i % 11) * 15 + 2;
        loc->y = (i / 11) * 6 + 2;
        E->loc = loc;

        if(i < 11){
            E->img1 = GW->images->farEnemy1;
            E->img2 = GW->images->farEnemy2;
        }
        else if(i < 33){
            E->img1 = GW->images->midEnemy1;
            E->img2 = GW->images->midEnemy2;
        }
        else{
            E->img1 = GW->images->nearEnemy1;
            E->img2 = GW->images->nearEnemy2;
        }

        enemyLL->E = E;
        if(i != 54){
            EnemyLL* nextLink = malloc(sizeof(EnemyLL));
            nextLink->next = NULL;
            nextLink->prev = enemyLL;
            enemyLL->next = nextLink;
            enemyLL = enemyLL->next;
        }
    }

    GW->ELL = first;
}

void renderEnemies(GameWindow* GW){
    // TODO add sprite alternation
    EnemyLL* e = GW->ELL;
    while(e){
        // TODO better naming lol
        if(GW->state)
            renderImg(GW,e->E->img1,e->E->loc->y,e->E->loc->x);
        else
            renderImg(GW,e->E->img2,e->E->loc->y,e->E->loc->x);
        e = e->next;
    }
}

void derenderEnemies(GameWindow* GW){
    // TODO add sprite alternation
    EnemyLL* e = GW->ELL;
    while(e){
        // TODO better naming lol
        if(GW->state)
            derenderImg(GW,e->E->img1,e->E->loc->y,e->E->loc->x);
        else
            derenderImg(GW,e->E->img2,e->E->loc->y,e->E->loc->x);
        e = e->next;
    }
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

