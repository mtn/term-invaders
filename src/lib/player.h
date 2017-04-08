#ifndef PLAYER_H
#define PLAYER_H

#include <ncurses.h>
#include <stdbool.h>

#include "main.h"


typedef struct {
    int health;
    Coord* loc;
} Player;

void initializePlayer(GameWindow* GW);
void movePlayerLeft(GameWindow* GW);
void movePlayerRight(GameWindow* GW);
void shootProjectile(GameWindow* GW);
void clearPlayer(GameWindow* GW);
void renderPlayer(GameWindow* GW);

#endif /* PLAYER_H */

