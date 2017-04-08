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

        Coord *C = calloc(1,sizeof(Coord));
        C->x = (i%11) << 1;
        C->y = (i/11) + 3;
        e->loc = C;
        enemies[i] = e;
    }
    GW->E = (void**)enemies;
}

// The enemies are essentially placed in a grid system
// This function computes location from index for all enemies
Coord* positionFromInd(int ind){
    Coord *position = malloc(sizeof(Coord));
    position->y = (4*ind/11) + 2;
    position->x = (ind % 11) * 14;
    return position;
}

void renderNear(GameWindow* GW, int ind){
    Coord *c = positionFromInd(ind);

    mvwaddstr(GW->W,c->y + 0, c->x, " ▄▄▄████▄▄▄ ");
    mvwaddstr(GW->W,c->y + 1, c->x, "███▀▀██▀▀███");
    mvwaddstr(GW->W,c->y + 2, c->x, "▀▀███▀▀███▀▀");
    mvwaddstr(GW->W,c->y + 3, c->x, " ▀█▄ ▀▀ ▄█▀ ");

    free(c);
}

void renderMedium(GameWindow* GW, int ind){
    Coord *c = positionFromInd(ind);

    mvwaddstr(GW->W,c->y + 0, c->x, "   ▀▄   ▄▀  ");
    mvwaddstr(GW->W,c->y + 1, c->x, "  ▄█▀███▀█▄ ");
    mvwaddstr(GW->W,c->y + 2, c->x, " █▀███████▀█");
    mvwaddstr(GW->W,c->y + 3, c->x, " ▀ ▀▄▄ ▄▄▀ ▀");

    free(c);
}

void renderFar(GameWindow* GW, int ind){
    Coord *c = positionFromInd(ind);

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
}

void shiftLeft(GameWindow* GW){

}

void shiftRight(GameWindow* GW){

}

