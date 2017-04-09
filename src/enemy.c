#define ENEMY_WIDTH 12

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

        enemies[i] = e;
    }
    GW->E = (void**)enemies;
    GW->enemyVertLoc = GW->enemyHorizLoc = 0;
    GW->enemyHorizBound = GW->boundX;
    GW->enemyVertBound = GW->boundY - 15;
}

// The enemies are essentially placed in a grid system
// This function computes position based on loc and relation to other enemies
Coord* positionFromInd(GameWindow* GW,int ind){
    Coord *position = malloc(sizeof(Coord));
    position->y = 2 + 5*(ind/11) + GW->enemyVertLoc;
    position->x = 2 + (ind % 11) * 14 + GW->enemyHorizLoc;
    return position;
}

void renderNear(GameWindow* GW, int ind){
    Coord *c = positionFromInd(GW,ind);

    mvwaddstr(GW->W,c->y + 0, c->x, " ▄▄▄████▄▄▄ ");
    mvwaddstr(GW->W,c->y + 1, c->x, "███▀▀██▀▀███");
    mvwaddstr(GW->W,c->y + 2, c->x, "▀▀███▀▀███▀▀");
    mvwaddstr(GW->W,c->y + 3, c->x, " ▀█▄ ▀▀ ▄█▀ ");

    free(c);
}

void renderMedium(GameWindow* GW, int ind){
    Coord *c = positionFromInd(GW,ind);

    mvwaddstr(GW->W,c->y + 0, c->x, "   ▀▄   ▄▀  ");
    mvwaddstr(GW->W,c->y + 1, c->x, "  ▄█▀███▀█▄ ");
    mvwaddstr(GW->W,c->y + 2, c->x, " █▀███████▀█");
    mvwaddstr(GW->W,c->y + 3, c->x, " ▀ ▀▄▄ ▄▄▀ ▀");

    free(c);
}

void renderFar(GameWindow* GW, int ind){
    Coord *c = positionFromInd(GW,ind);

    mvwaddstr(GW->W,c->y + 0, c->x, "    ▄██▄    ");
    mvwaddstr(GW->W,c->y + 1, c->x, "  ▄█▀██▀█▄  ");
    mvwaddstr(GW->W,c->y + 2, c->x, "  ▀▀█▀▀█▀▀  ");
    mvwaddstr(GW->W,c->y + 3, c->x, "  ▄▀▄▀▀▄▀▄  ");

    free(c);
}

void renderEnemies(GameWindow* GW){
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
        c = positionFromInd(GW,i);
        locy = c->y;

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

