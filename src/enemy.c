#define ENEMY_WIDTH  7
#define NUM_ENEMIES 35
#define NUM_COLS     7

#include <stdlib.h>

#include "lib/main.h"
#include "lib/enemy.h"

void initializeEnemies(GameWindow* GW){
    EnemyLL* enemyLL = malloc(sizeof(EnemyLL));
    enemyLL->prev = NULL;
    enemyLL->next = NULL;
    EnemyLL* first = enemyLL;

    // Approx. half the screen occupied at at time
    int horizOffset = (int)((GW->boundX)/15);
    int vertOffset = 6;
    for(int i = 0; i < NUM_ENEMIES; ++i){
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
        enemyLL->E = E;
        if(i != NUM_ENEMIES-1){
            EnemyLL* nextLink = malloc(sizeof(EnemyLL));
            nextLink->next = NULL;
            nextLink->prev = enemyLL;
            enemyLL->next = nextLink;
            enemyLL = enemyLL->next;
        }
    }

    GW->enemyHorizOffset = horizOffset;
    GW->enemyVertOffset = horizOffset;

    GW->ELL = first;
}

void renderEnemies(GameWindow* GW){
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
    EnemyLL* e = GW->ELL;
    while(e){
        if(GW->state)
            renderImg(GW,e->E->img1,e->E->loc->y,e->E->loc->x);
        else
            renderImg(GW,e->E->img2,e->E->loc->y,e->E->loc->x);
        e = e->next;
    }
}

bool moveEnemyBlockDown(GameWindow* GW){
    EnemyLL* e = GW->ELL;
    while(e){
        derenderImg(GW,e->E->img1,e->E->loc->y,e->E->loc->x); // img1/img2 don't matter for derender
        ++e->E->loc->y;
        if(GW->state)
            renderImg(GW,e->E->img1,e->E->loc->y,e->E->loc->x);
        else
            renderImg(GW,e->E->img2,e->E->loc->y,e->E->loc->x);
        if(e->E->loc->y > GW->boundY - 8) return false;
        e = e->next;
    }
    return true;
}

void moveEnemyBlockLeft(GameWindow* GW){
    EnemyLL* e = GW->ELL;
    while(e){
        if(e->E){
            derenderImg(GW,e->E->img1,e->E->loc->y,e->E->loc->x);
            --e->E->loc->x;
            if(e->E->loc->x == 1 && GW->shiftDir == LEFT){
                GW->shiftDir = RIGHT;
                moveEnemyBlockDown(GW);
            }
        }
        e = e->next;
    }
    wrefresh(GW->W);
}

void moveEnemyBlockRight(GameWindow* GW){
    EnemyLL* e = GW->ELL;
    while(e){
        if(e->E){
            derenderImg(GW,e->E->img1,e->E->loc->y,e->E->loc->x);
            ++e->E->loc->x;
            if(e->E->loc->x == GW->boundX - ENEMY_WIDTH){
                GW->shiftDir = LEFT;
            }
        }
        e = e->next;
    }
    wrefresh(GW->W);
}

