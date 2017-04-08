#define MAX_HEALTH 100
#define PLAYER_WIDTH  12

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

void movePlayerLeft(GameWindow* GW){
    if(((Player*)GW->P)->loc->x > 1){
        clearPlayer(GW);
        --((Player*)GW->P)->loc->x;
    }
    wrefresh(GW->W);
}

void movePlayerRight(GameWindow* GW){
    if(((Player*)GW->P)->loc->x < (GW->boundX - PLAYER_WIDTH)){
        clearPlayer(GW);
        ++((Player*)GW->P)->loc->x;
    }
    wrefresh(GW->W);
}

void shootProjectile(GameWindow* GW){
    // TODO
}

// Clears the currently rendered player
void clearPlayer(GameWindow* GW){
    int locx = ((Player*)GW->P)->loc->x;
    int locy = ((Player*)GW->P)->loc->y;

    wmove(GW->W,locy-3, 0);
    wclrtoeol(GW->W);
    wmove(GW->W,locy-2, 0);
    wclrtoeol(GW->W);
    wmove(GW->W,locy-1, 0);
    wclrtoeol(GW->W);

    // Box gets ruined
    box(GW->W,0,0);
}

void renderPlayer(GameWindow* gameWin){
    attron(COLOR_PAIR(1));
    mvwaddstr(gameWin->W,((Player*)gameWin->P)->loc->y-3, ((Player*)gameWin->P)->loc->x, "    ▄█▄    ");
    mvwaddstr(gameWin->W,((Player*)gameWin->P)->loc->y-2, ((Player*)gameWin->P)->loc->x, "▄█████████▄");
    mvwaddstr(gameWin->W,((Player*)gameWin->P)->loc->y-1, ((Player*)gameWin->P)->loc->x, "▀▀▀▀▀▀▀▀▀▀▀");
    attroff(COLOR_PAIR(1));
    wrefresh(gameWin->W);
}

