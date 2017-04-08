#define MAX_HEALTH 100

#include <stdlib.h>

#include "lib/player.h"

void addPlayer(GameWindow* gameWin){
    int maxY, maxX;
    getmaxyx(gameWin->W,maxY,maxX);

    Player *P = calloc(1,sizeof(Player));
    P->health = MAX_HEALTH;
    Coord *playerLoc = calloc(1,sizeof(Coord));
    playerLoc->x = (int)(maxX/2);
    playerLoc->y = maxY-3;
    P->loc = playerLoc;
    gameWin->P = P;
}

void renderPlayer(GameWindow* gameWin){
    Player* P = (Player*)gameWin->P;
    wmvaddch(gameWin->W,P->loc->y,P->loc->x,'^');
    wrefresh(gameWin->W);
}

