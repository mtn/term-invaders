#define MAX_HEALTH 100

#include <stdlib.h>

#include "lib/player.h"

void initializePlayer(GameWindow* gameWin){
    int maxY, maxX;
    getmaxyx(gameWin->W,maxY,maxX);

    Player *P = calloc(1,sizeof(Player));
    P->health = MAX_HEALTH;
    Coord *playerLoc = calloc(1,sizeof(Coord));
    playerLoc->x = (int)(maxX/2);
    playerLoc->y = maxY-3; P->loc = playerLoc;
    gameWin->P = P;
}

void moveLeft(GameWindow* GW){
    --((Player*)GW->P)->loc->x;
}

void moveRight(GameWindow* GW){
    ++((Player*)GW->P)->loc->x;
}

void shootProjectile(GameWindow* GW){
    // TODO
}

void renderPlayer(GameWindow* gameWin){
    attron(COLOR_PAIR(1));
    mvwaddstr(gameWin->W,((Player*)gameWin->P)->loc->y-3, ((Player*)gameWin->P)->loc->x, "    ▄█▄    ");
    mvwaddstr(gameWin->W,((Player*)gameWin->P)->loc->y-2, ((Player*)gameWin->P)->loc->x, "▄█████████▄");
    mvwaddstr(gameWin->W,((Player*)gameWin->P)->loc->y-1, ((Player*)gameWin->P)->loc->x, "▀▀▀▀▀▀▀▀▀▀▀");
    attroff(COLOR_PAIR(1));
    /* wmvaddch(gameWin->W,P->loc->y,P->loc->x,'^'); */
    wrefresh(gameWin->W);
}

