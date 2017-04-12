#define MAX_HEALTH   100

#include <stdlib.h>

#include "lib/player.h"
#include "lib/main.h"

void initializePlayer(GameWindow* GW){
    Player *P = malloc(sizeof(Player));
    P->img = GW->images->player;
    P->health = MAX_HEALTH;

    Coord *playerLoc = malloc(sizeof(Coord));
    playerLoc->x = (int)(GW->boundX/2);
    playerLoc->y = GW->boundY-4; P->loc = playerLoc;

    GW->P = P;
}

void renderPlayer(GameWindow* GW){
    renderImg(GW,GW->P->img,GW->P->loc->y,GW->P->loc->x);
    wrefresh(GW->W);
}

void derenderPlayer(GameWindow* GW){
    derenderImg(GW,GW->P->img,GW->P->loc->y,GW->P->loc->x);
    wrefresh(GW->W);
}

void movePlayerLeft(GameWindow* GW){
    if(GW->P->loc->x > 1){
        derenderImg(GW,GW->P->img,GW->P->loc->y,GW->P->loc->x);
        --GW->P->loc->x;
    }
    wrefresh(GW->W);
}

void movePlayerRight(GameWindow* GW){
    if(GW->P->loc->x < (GW->boundX - GW->P->img->xDim)){
        derenderImg(GW,GW->P->img,GW->P->loc->y,GW->P->loc->x);
        ++GW->P->loc->x;
    }
    wrefresh(GW->W);
}

void shootProjectile(GameWindow* GW){
    // TODO
}

